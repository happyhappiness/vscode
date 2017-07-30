; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/block_header_decoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_block = type { i32, i32, i32, i64, i64, %struct.lzma_filter*, [64 x i8], i8*, i8*, i8*, i32, i32, i64, i64, i64, i64, i64, i64, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8, i8, i8 }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }

; Function Attrs: nounwind uwtable
define i32 @lzma_block_header_decode(%struct.lzma_block* %block, %struct.lzma_allocator* %allocator, i8* %in) #0 !dbg !36 {
entry:
  %retval = alloca i32, align 4
  %block.addr = alloca %struct.lzma_block*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %in.addr = alloca i8*, align 8
  %filter_count = alloca i64, align 8
  %in_size = alloca i64, align 8
  %i = alloca i64, align 8
  %in_pos = alloca i64, align 8
  %ret_ = alloca i32, align 4
  %ret_48 = alloca i32, align 4
  %ret = alloca i32, align 4
  store %struct.lzma_block* %block, %struct.lzma_block** %block.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_block** %block.addr, metadata !122, metadata !123), !dbg !124
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !125, metadata !123), !dbg !126
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !127, metadata !123), !dbg !128
  call void @llvm.dbg.declare(metadata i64* %filter_count, metadata !129, metadata !123), !dbg !131
  %0 = load i8*, i8** %in.addr, align 8, !dbg !132
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 1, !dbg !132
  %1 = load i8, i8* %arrayidx, align 1, !dbg !132
  %conv = zext i8 %1 to i32, !dbg !132
  %and = and i32 %conv, 3, !dbg !133
  %add = add nsw i32 %and, 1, !dbg !134
  %conv1 = sext i32 %add to i64, !dbg !135
  store i64 %conv1, i64* %filter_count, align 8, !dbg !131
  call void @llvm.dbg.declare(metadata i64* %in_size, metadata !136, metadata !123), !dbg !137
  call void @llvm.dbg.declare(metadata i64* %i, metadata !138, metadata !123), !dbg !139
  call void @llvm.dbg.declare(metadata i64* %in_pos, metadata !140, metadata !123), !dbg !141
  store i64 2, i64* %in_pos, align 8, !dbg !141
  store i64 0, i64* %i, align 8, !dbg !142
  br label %for.cond, !dbg !144

for.cond:                                         ; preds = %for.inc, %entry
  %2 = load i64, i64* %i, align 8, !dbg !145
  %cmp = icmp ule i64 %2, 4, !dbg !148
  br i1 %cmp, label %for.body, label %for.end, !dbg !149

for.body:                                         ; preds = %for.cond
  %3 = load i64, i64* %i, align 8, !dbg !150
  %4 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !152
  %filters = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %4, i32 0, i32 5, !dbg !153
  %5 = load %struct.lzma_filter*, %struct.lzma_filter** %filters, align 8, !dbg !153
  %arrayidx3 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %5, i64 %3, !dbg !152
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx3, i32 0, i32 0, !dbg !154
  store i64 -1, i64* %id, align 8, !dbg !155
  %6 = load i64, i64* %i, align 8, !dbg !156
  %7 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !157
  %filters4 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %7, i32 0, i32 5, !dbg !158
  %8 = load %struct.lzma_filter*, %struct.lzma_filter** %filters4, align 8, !dbg !158
  %arrayidx5 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %8, i64 %6, !dbg !157
  %options = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx5, i32 0, i32 1, !dbg !159
  store i8* null, i8** %options, align 8, !dbg !160
  br label %for.inc, !dbg !161

for.inc:                                          ; preds = %for.body
  %9 = load i64, i64* %i, align 8, !dbg !162
  %inc = add i64 %9, 1, !dbg !162
  store i64 %inc, i64* %i, align 8, !dbg !162
  br label %for.cond, !dbg !164

for.end:                                          ; preds = %for.cond
  %10 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !165
  %version = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %10, i32 0, i32 0, !dbg !166
  store i32 0, i32* %version, align 8, !dbg !167
  %11 = load i8*, i8** %in.addr, align 8, !dbg !168
  %arrayidx6 = getelementptr inbounds i8, i8* %11, i64 0, !dbg !168
  %12 = load i8, i8* %arrayidx6, align 1, !dbg !168
  %conv7 = zext i8 %12 to i32, !dbg !168
  %add8 = add i32 %conv7, 1, !dbg !168
  %mul = mul i32 %add8, 4, !dbg !168
  %13 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !170
  %header_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %13, i32 0, i32 1, !dbg !171
  %14 = load i32, i32* %header_size, align 4, !dbg !171
  %cmp9 = icmp ne i32 %mul, %14, !dbg !172
  br i1 %cmp9, label %if.then, label %lor.lhs.false, !dbg !173

lor.lhs.false:                                    ; preds = %for.end
  %15 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !174
  %check = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %15, i32 0, i32 2, !dbg !176
  %16 = load i32, i32* %check, align 8, !dbg !176
  %cmp11 = icmp ugt i32 %16, 15, !dbg !177
  br i1 %cmp11, label %if.then, label %if.end, !dbg !178

if.then:                                          ; preds = %lor.lhs.false, %for.end
  store i32 11, i32* %retval, align 4, !dbg !180
  br label %return, !dbg !180

if.end:                                           ; preds = %lor.lhs.false
  %17 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !181
  %header_size13 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %17, i32 0, i32 1, !dbg !182
  %18 = load i32, i32* %header_size13, align 4, !dbg !182
  %sub = sub i32 %18, 4, !dbg !183
  %conv14 = zext i32 %sub to i64, !dbg !181
  store i64 %conv14, i64* %in_size, align 8, !dbg !184
  %19 = load i8*, i8** %in.addr, align 8, !dbg !185
  %20 = load i64, i64* %in_size, align 8, !dbg !187
  %call = call i32 @lzma_crc32(i8* %19, i64 %20, i32 0) #6, !dbg !188
  %21 = load i8*, i8** %in.addr, align 8, !dbg !189
  %22 = load i64, i64* %in_size, align 8, !dbg !190
  %add.ptr = getelementptr inbounds i8, i8* %21, i64 %22, !dbg !191
  %call15 = call i32 @read32le(i8* %add.ptr), !dbg !192
  %cmp16 = icmp ne i32 %call, %call15, !dbg !194
  br i1 %cmp16, label %if.then18, label %if.end19, !dbg !195

if.then18:                                        ; preds = %if.end
  store i32 9, i32* %retval, align 4, !dbg !196
  br label %return, !dbg !196

if.end19:                                         ; preds = %if.end
  %23 = load i8*, i8** %in.addr, align 8, !dbg !197
  %arrayidx20 = getelementptr inbounds i8, i8* %23, i64 1, !dbg !197
  %24 = load i8, i8* %arrayidx20, align 1, !dbg !197
  %conv21 = zext i8 %24 to i32, !dbg !197
  %and22 = and i32 %conv21, 60, !dbg !199
  %tobool = icmp ne i32 %and22, 0, !dbg !199
  br i1 %tobool, label %if.then23, label %if.end24, !dbg !200

if.then23:                                        ; preds = %if.end19
  store i32 8, i32* %retval, align 4, !dbg !201
  br label %return, !dbg !201

if.end24:                                         ; preds = %if.end19
  %25 = load i8*, i8** %in.addr, align 8, !dbg !202
  %arrayidx25 = getelementptr inbounds i8, i8* %25, i64 1, !dbg !202
  %26 = load i8, i8* %arrayidx25, align 1, !dbg !202
  %conv26 = zext i8 %26 to i32, !dbg !202
  %and27 = and i32 %conv26, 64, !dbg !204
  %tobool28 = icmp ne i32 %and27, 0, !dbg !204
  br i1 %tobool28, label %if.then29, label %if.else, !dbg !205

if.then29:                                        ; preds = %if.end24
  br label %do.body, !dbg !206

do.body:                                          ; preds = %if.then29
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !208, metadata !123), !dbg !211
  %27 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !212
  %compressed_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %27, i32 0, i32 3, !dbg !212
  %28 = load i8*, i8** %in.addr, align 8, !dbg !212
  %29 = load i64, i64* %in_size, align 8, !dbg !212
  %call30 = call i32 @lzma_vli_decode(i64* %compressed_size, i64* null, i8* %28, i64* %in_pos, i64 %29) #7, !dbg !212
  store i32 %call30, i32* %ret_, align 4, !dbg !212
  %30 = load i32, i32* %ret_, align 4, !dbg !212
  %cmp31 = icmp ne i32 %30, 0, !dbg !212
  br i1 %cmp31, label %if.then33, label %if.end34, !dbg !212

if.then33:                                        ; preds = %do.body
  %31 = load i32, i32* %ret_, align 4, !dbg !214
  store i32 %31, i32* %retval, align 4, !dbg !214
  br label %return, !dbg !214

if.end34:                                         ; preds = %do.body
  br label %do.end, !dbg !217

do.end:                                           ; preds = %if.end34
  %32 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !219
  %call35 = call i64 @lzma_block_unpadded_size(%struct.lzma_block* %32) #6, !dbg !221
  %cmp36 = icmp eq i64 %call35, 0, !dbg !222
  br i1 %cmp36, label %if.then38, label %if.end39, !dbg !223

if.then38:                                        ; preds = %do.end
  store i32 9, i32* %retval, align 4, !dbg !224
  br label %return, !dbg !224

if.end39:                                         ; preds = %do.end
  br label %if.end41, !dbg !225

if.else:                                          ; preds = %if.end24
  %33 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !226
  %compressed_size40 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %33, i32 0, i32 3, !dbg !228
  store i64 -1, i64* %compressed_size40, align 8, !dbg !229
  br label %if.end41

if.end41:                                         ; preds = %if.else, %if.end39
  %34 = load i8*, i8** %in.addr, align 8, !dbg !230
  %arrayidx42 = getelementptr inbounds i8, i8* %34, i64 1, !dbg !230
  %35 = load i8, i8* %arrayidx42, align 1, !dbg !230
  %conv43 = zext i8 %35 to i32, !dbg !230
  %and44 = and i32 %conv43, 128, !dbg !232
  %tobool45 = icmp ne i32 %and44, 0, !dbg !232
  br i1 %tobool45, label %if.then46, label %if.else55, !dbg !233

if.then46:                                        ; preds = %if.end41
  br label %do.body47, !dbg !234

do.body47:                                        ; preds = %if.then46
  call void @llvm.dbg.declare(metadata i32* %ret_48, metadata !235, metadata !123), !dbg !237
  %36 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !238
  %uncompressed_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %36, i32 0, i32 4, !dbg !238
  %37 = load i8*, i8** %in.addr, align 8, !dbg !238
  %38 = load i64, i64* %in_size, align 8, !dbg !238
  %call49 = call i32 @lzma_vli_decode(i64* %uncompressed_size, i64* null, i8* %37, i64* %in_pos, i64 %38) #7, !dbg !238
  store i32 %call49, i32* %ret_48, align 4, !dbg !238
  %39 = load i32, i32* %ret_48, align 4, !dbg !238
  %cmp50 = icmp ne i32 %39, 0, !dbg !238
  br i1 %cmp50, label %if.then52, label %if.end53, !dbg !238

if.then52:                                        ; preds = %do.body47
  %40 = load i32, i32* %ret_48, align 4, !dbg !240
  store i32 %40, i32* %retval, align 4, !dbg !240
  br label %return, !dbg !240

if.end53:                                         ; preds = %do.body47
  br label %do.end54, !dbg !243

do.end54:                                         ; preds = %if.end53
  br label %if.end57, !dbg !245

if.else55:                                        ; preds = %if.end41
  %41 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !247
  %uncompressed_size56 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %41, i32 0, i32 4, !dbg !248
  store i64 -1, i64* %uncompressed_size56, align 8, !dbg !249
  br label %if.end57

if.end57:                                         ; preds = %if.else55, %do.end54
  store i64 0, i64* %i, align 8, !dbg !250
  br label %for.cond58, !dbg !252

for.cond58:                                       ; preds = %for.inc69, %if.end57
  %42 = load i64, i64* %i, align 8, !dbg !253
  %43 = load i64, i64* %filter_count, align 8, !dbg !256
  %cmp59 = icmp ult i64 %42, %43, !dbg !257
  br i1 %cmp59, label %for.body61, label %for.end71, !dbg !258

for.body61:                                       ; preds = %for.cond58
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !259, metadata !123), !dbg !261
  %44 = load i64, i64* %i, align 8, !dbg !262
  %45 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !263
  %filters62 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %45, i32 0, i32 5, !dbg !264
  %46 = load %struct.lzma_filter*, %struct.lzma_filter** %filters62, align 8, !dbg !264
  %arrayidx63 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %46, i64 %44, !dbg !263
  %47 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !265
  %48 = load i8*, i8** %in.addr, align 8, !dbg !266
  %49 = load i64, i64* %in_size, align 8, !dbg !267
  %call64 = call i32 @lzma_filter_flags_decode(%struct.lzma_filter* %arrayidx63, %struct.lzma_allocator* %47, i8* %48, i64* %in_pos, i64 %49) #7, !dbg !268
  store i32 %call64, i32* %ret, align 4, !dbg !261
  %50 = load i32, i32* %ret, align 4, !dbg !269
  %cmp65 = icmp ne i32 %50, 0, !dbg !271
  br i1 %cmp65, label %if.then67, label %if.end68, !dbg !272

if.then67:                                        ; preds = %for.body61
  %51 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !273
  %52 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !275
  call void @free_properties(%struct.lzma_block* %51, %struct.lzma_allocator* %52), !dbg !276
  %53 = load i32, i32* %ret, align 4, !dbg !277
  store i32 %53, i32* %retval, align 4, !dbg !278
  br label %return, !dbg !278

if.end68:                                         ; preds = %for.body61
  br label %for.inc69, !dbg !279

for.inc69:                                        ; preds = %if.end68
  %54 = load i64, i64* %i, align 8, !dbg !280
  %inc70 = add i64 %54, 1, !dbg !280
  store i64 %inc70, i64* %i, align 8, !dbg !280
  br label %for.cond58, !dbg !282

for.end71:                                        ; preds = %for.cond58
  br label %while.cond, !dbg !283

while.cond:                                       ; preds = %if.end80, %for.end71
  %55 = load i64, i64* %in_pos, align 8, !dbg !284
  %56 = load i64, i64* %in_size, align 8, !dbg !285
  %cmp72 = icmp ult i64 %55, %56, !dbg !286
  br i1 %cmp72, label %while.body, label %while.end, !dbg !287

while.body:                                       ; preds = %while.cond
  %57 = load i64, i64* %in_pos, align 8, !dbg !288
  %inc74 = add i64 %57, 1, !dbg !288
  store i64 %inc74, i64* %in_pos, align 8, !dbg !288
  %58 = load i8*, i8** %in.addr, align 8, !dbg !291
  %arrayidx75 = getelementptr inbounds i8, i8* %58, i64 %57, !dbg !291
  %59 = load i8, i8* %arrayidx75, align 1, !dbg !291
  %conv76 = zext i8 %59 to i32, !dbg !291
  %cmp77 = icmp ne i32 %conv76, 0, !dbg !292
  br i1 %cmp77, label %if.then79, label %if.end80, !dbg !293

if.then79:                                        ; preds = %while.body
  %60 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !294
  %61 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !296
  call void @free_properties(%struct.lzma_block* %60, %struct.lzma_allocator* %61), !dbg !297
  store i32 8, i32* %retval, align 4, !dbg !298
  br label %return, !dbg !298

if.end80:                                         ; preds = %while.body
  br label %while.cond, !dbg !299

while.end:                                        ; preds = %while.cond
  store i32 0, i32* %retval, align 4, !dbg !301
  br label %return, !dbg !301

return:                                           ; preds = %while.end, %if.then79, %if.then67, %if.then52, %if.then38, %if.then33, %if.then23, %if.then18, %if.then
  %62 = load i32, i32* %retval, align 4, !dbg !302
  ret i32 %62, !dbg !302
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind readonly
declare i32 @lzma_crc32(i8*, i64, i32) #2

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @read32le(i8* %buf) #3 !dbg !112 {
entry:
  %buf.addr = alloca i8*, align 8
  %num = alloca i32, align 4
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !303, metadata !123), !dbg !304
  call void @llvm.dbg.declare(metadata i32* %num, metadata !305, metadata !123), !dbg !306
  %0 = load i8*, i8** %buf.addr, align 8, !dbg !307
  %1 = bitcast i8* %0 to i32*, !dbg !308
  %2 = load i32, i32* %1, align 4, !dbg !308
  store i32 %2, i32* %num, align 4, !dbg !306
  %3 = load i32, i32* %num, align 4, !dbg !309
  ret i32 %3, !dbg !310
}

; Function Attrs: nounwind
declare i32 @lzma_vli_decode(i64*, i64*, i8*, i64*, i64) #4

; Function Attrs: nounwind readonly
declare i64 @lzma_block_unpadded_size(%struct.lzma_block*) #2

; Function Attrs: nounwind
declare i32 @lzma_filter_flags_decode(%struct.lzma_filter*, %struct.lzma_allocator*, i8*, i64*, i64) #4

; Function Attrs: nounwind uwtable
define internal void @free_properties(%struct.lzma_block* %block, %struct.lzma_allocator* %allocator) #0 !dbg !116 {
entry:
  %block.addr = alloca %struct.lzma_block*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %i = alloca i64, align 8
  store %struct.lzma_block* %block, %struct.lzma_block** %block.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_block** %block.addr, metadata !311, metadata !123), !dbg !312
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !313, metadata !123), !dbg !314
  call void @llvm.dbg.declare(metadata i64* %i, metadata !315, metadata !123), !dbg !316
  store i64 0, i64* %i, align 8, !dbg !317
  br label %for.cond, !dbg !319

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i64, i64* %i, align 8, !dbg !320
  %cmp = icmp ult i64 %0, 4, !dbg !323
  br i1 %cmp, label %for.body, label %for.end, !dbg !324

for.body:                                         ; preds = %for.cond
  %1 = load i64, i64* %i, align 8, !dbg !325
  %2 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !327
  %filters = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %2, i32 0, i32 5, !dbg !328
  %3 = load %struct.lzma_filter*, %struct.lzma_filter** %filters, align 8, !dbg !328
  %arrayidx = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %3, i64 %1, !dbg !327
  %options = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx, i32 0, i32 1, !dbg !329
  %4 = load i8*, i8** %options, align 8, !dbg !329
  %5 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !330
  call void @lzma_free(i8* %4, %struct.lzma_allocator* %5), !dbg !331
  %6 = load i64, i64* %i, align 8, !dbg !332
  %7 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !333
  %filters1 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %7, i32 0, i32 5, !dbg !334
  %8 = load %struct.lzma_filter*, %struct.lzma_filter** %filters1, align 8, !dbg !334
  %arrayidx2 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %8, i64 %6, !dbg !333
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx2, i32 0, i32 0, !dbg !335
  store i64 -1, i64* %id, align 8, !dbg !336
  %9 = load i64, i64* %i, align 8, !dbg !337
  %10 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !338
  %filters3 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %10, i32 0, i32 5, !dbg !339
  %11 = load %struct.lzma_filter*, %struct.lzma_filter** %filters3, align 8, !dbg !339
  %arrayidx4 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %11, i64 %9, !dbg !338
  %options5 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx4, i32 0, i32 1, !dbg !340
  store i8* null, i8** %options5, align 8, !dbg !341
  br label %for.inc, !dbg !342

for.inc:                                          ; preds = %for.body
  %12 = load i64, i64* %i, align 8, !dbg !343
  %inc = add i64 %12, 1, !dbg !343
  store i64 %inc, i64* %i, align 8, !dbg !343
  br label %for.cond, !dbg !345

for.end:                                          ; preds = %for.cond
  ret void, !dbg !346
}

declare void @lzma_free(i8*, %struct.lzma_allocator*) #5

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly }
attributes #7 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!119, !120}
!llvm.ident = !{!121}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !28, subprograms: !35)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/block_header_decoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !25}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 57, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/base.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17}
!6 = !DIEnumerator(name: "LZMA_OK", value: 0)
!7 = !DIEnumerator(name: "LZMA_STREAM_END", value: 1)
!8 = !DIEnumerator(name: "LZMA_NO_CHECK", value: 2)
!9 = !DIEnumerator(name: "LZMA_UNSUPPORTED_CHECK", value: 3)
!10 = !DIEnumerator(name: "LZMA_GET_CHECK", value: 4)
!11 = !DIEnumerator(name: "LZMA_MEM_ERROR", value: 5)
!12 = !DIEnumerator(name: "LZMA_MEMLIMIT_ERROR", value: 6)
!13 = !DIEnumerator(name: "LZMA_FORMAT_ERROR", value: 7)
!14 = !DIEnumerator(name: "LZMA_OPTIONS_ERROR", value: 8)
!15 = !DIEnumerator(name: "LZMA_DATA_ERROR", value: 9)
!16 = !DIEnumerator(name: "LZMA_BUF_ERROR", value: 10)
!17 = !DIEnumerator(name: "LZMA_PROG_ERROR", value: 11)
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !19, line: 27, size: 32, align: 32, elements: !20)
!19 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!20 = !{!21, !22, !23, !24}
!21 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!22 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!23 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!24 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!25 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !26)
!26 = !{!27}
!27 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!28 = !{!29, !30, !32, !33}
!29 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!30 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !31, line: 51, baseType: !32)
!31 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!32 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!33 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !34, size: 64, align: 64)
!34 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !30)
!35 = !{!36, !112, !116}
!36 = distinct !DISubprogram(name: "lzma_block_header_decode", scope: !1, file: !1, line: 36, type: !37, isLocal: false, isDefinition: true, scopeLine: 38, flags: DIFlagPrototyped, isOptimized: false, variables: !111)
!37 = !DISubroutineType(types: !38)
!38 = !{!39, !40, !94, !109}
!39 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!40 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !41, size: 64, align: 64)
!41 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_block", file: !42, line: 245, baseType: !43)
!42 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/block.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!43 = !DICompositeType(tag: DW_TAG_structure_type, file: !42, line: 30, size: 1664, align: 64, elements: !44)
!44 = !{!45, !46, !47, !49, !54, !55, !63, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !82, !83, !84, !85, !87, !88, !89, !90, !91, !92, !93}
!45 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !43, file: !42, line: 47, baseType: !30, size: 32, align: 32)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "header_size", scope: !43, file: !42, line: 67, baseType: !30, size: 32, align: 32, offset: 32)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !43, file: !42, line: 88, baseType: !48, size: 32, align: 32, offset: 64)
!48 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !19, line: 55, baseType: !18)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_size", scope: !43, file: !42, line: 143, baseType: !50, size: 64, align: 64, offset: 128)
!50 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !51, line: 63, baseType: !52)
!51 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !31, line: 55, baseType: !53)
!53 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !43, file: !42, line: 167, baseType: !50, size: 64, align: 64, offset: 192)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "filters", scope: !43, file: !42, line: 195, baseType: !56, size: 64, align: 64, offset: 256)
!56 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64, align: 64)
!57 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !58, line: 65, baseType: !59)
!58 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!59 = !DICompositeType(tag: DW_TAG_structure_type, file: !58, line: 43, size: 128, align: 64, elements: !60)
!60 = !{!61, !62}
!61 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !59, file: !58, line: 54, baseType: !50, size: 64, align: 64)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !59, file: !58, line: 63, baseType: !29, size: 64, align: 64, offset: 64)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "raw_check", scope: !43, file: !42, line: 212, baseType: !64, size: 512, align: 8, offset: 320)
!64 = !DICompositeType(tag: DW_TAG_array_type, baseType: !65, size: 512, align: 8, elements: !67)
!65 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !31, line: 48, baseType: !66)
!66 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!67 = !{!68}
!68 = !DISubrange(count: 64)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !43, file: !42, line: 221, baseType: !29, size: 64, align: 64, offset: 832)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !43, file: !42, line: 222, baseType: !29, size: 64, align: 64, offset: 896)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !43, file: !42, line: 223, baseType: !29, size: 64, align: 64, offset: 960)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !43, file: !42, line: 224, baseType: !30, size: 32, align: 32, offset: 1024)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !43, file: !42, line: 225, baseType: !30, size: 32, align: 32, offset: 1056)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !43, file: !42, line: 226, baseType: !50, size: 64, align: 64, offset: 1088)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !43, file: !42, line: 227, baseType: !50, size: 64, align: 64, offset: 1152)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !43, file: !42, line: 228, baseType: !50, size: 64, align: 64, offset: 1216)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !43, file: !42, line: 229, baseType: !50, size: 64, align: 64, offset: 1280)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !43, file: !42, line: 230, baseType: !50, size: 64, align: 64, offset: 1344)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !43, file: !42, line: 231, baseType: !50, size: 64, align: 64, offset: 1408)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !43, file: !42, line: 232, baseType: !81, size: 32, align: 32, offset: 1472)
!81 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !25)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !43, file: !42, line: 233, baseType: !81, size: 32, align: 32, offset: 1504)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !43, file: !42, line: 234, baseType: !81, size: 32, align: 32, offset: 1536)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !43, file: !42, line: 235, baseType: !81, size: 32, align: 32, offset: 1568)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool1", scope: !43, file: !42, line: 236, baseType: !86, size: 8, align: 8, offset: 1600)
!86 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !4, line: 29, baseType: !66)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool2", scope: !43, file: !42, line: 237, baseType: !86, size: 8, align: 8, offset: 1608)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool3", scope: !43, file: !42, line: 238, baseType: !86, size: 8, align: 8, offset: 1616)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool4", scope: !43, file: !42, line: 239, baseType: !86, size: 8, align: 8, offset: 1624)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool5", scope: !43, file: !42, line: 240, baseType: !86, size: 8, align: 8, offset: 1632)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool6", scope: !43, file: !42, line: 241, baseType: !86, size: 8, align: 8, offset: 1640)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool7", scope: !43, file: !42, line: 242, baseType: !86, size: 8, align: 8, offset: 1648)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool8", scope: !43, file: !42, line: 243, baseType: !86, size: 8, align: 8, offset: 1656)
!94 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !95, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !96)
!96 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !97)
!97 = !{!98, !104, !108}
!98 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !96, file: !4, line: 376, baseType: !99, size: 64, align: 64)
!99 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !100, size: 64, align: 64)
!100 = !DISubroutineType(types: !101)
!101 = !{!29, !29, !102, !102}
!102 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !103, line: 62, baseType: !53)
!103 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!104 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !96, file: !4, line: 390, baseType: !105, size: 64, align: 64, offset: 64)
!105 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !106, size: 64, align: 64)
!106 = !DISubroutineType(types: !107)
!107 = !{null, !29, !29}
!108 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !96, file: !4, line: 401, baseType: !29, size: 64, align: 64, offset: 128)
!109 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !110, size: 64, align: 64)
!110 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !65)
!111 = !{}
!112 = distinct !DISubprogram(name: "read32le", scope: !113, file: !113, line: 209, type: !114, isLocal: true, isDefinition: true, scopeLine: 210, flags: DIFlagPrototyped, isOptimized: false, variables: !111)
!113 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/common/tuklib_integer.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!114 = !DISubroutineType(types: !115)
!115 = !{!30, !109}
!116 = distinct !DISubprogram(name: "free_properties", scope: !1, file: !1, line: 18, type: !117, isLocal: true, isDefinition: true, scopeLine: 19, flags: DIFlagPrototyped, isOptimized: false, variables: !111)
!117 = !DISubroutineType(types: !118)
!118 = !{null, !40, !94}
!119 = !{i32 2, !"Dwarf Version", i32 4}
!120 = !{i32 2, !"Debug Info Version", i32 3}
!121 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!122 = !DILocalVariable(name: "block", arg: 1, scope: !36, file: !1, line: 36, type: !40)
!123 = !DIExpression()
!124 = !DILocation(line: 36, column: 38, scope: !36)
!125 = !DILocalVariable(name: "allocator", arg: 2, scope: !36, file: !1, line: 37, type: !94)
!126 = !DILocation(line: 37, column: 19, scope: !36)
!127 = !DILocalVariable(name: "in", arg: 3, scope: !36, file: !1, line: 37, type: !109)
!128 = !DILocation(line: 37, column: 45, scope: !36)
!129 = !DILocalVariable(name: "filter_count", scope: !36, file: !1, line: 39, type: !130)
!130 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !102)
!131 = !DILocation(line: 39, column: 15, scope: !36)
!132 = !DILocation(line: 39, column: 31, scope: !36)
!133 = !DILocation(line: 39, column: 37, scope: !36)
!134 = !DILocation(line: 39, column: 42, scope: !36)
!135 = !DILocation(line: 39, column: 30, scope: !36)
!136 = !DILocalVariable(name: "in_size", scope: !36, file: !1, line: 40, type: !102)
!137 = !DILocation(line: 40, column: 9, scope: !36)
!138 = !DILocalVariable(name: "i", scope: !36, file: !1, line: 41, type: !102)
!139 = !DILocation(line: 41, column: 9, scope: !36)
!140 = !DILocalVariable(name: "in_pos", scope: !36, file: !1, line: 44, type: !102)
!141 = !DILocation(line: 44, column: 9, scope: !36)
!142 = !DILocation(line: 53, column: 9, scope: !143)
!143 = distinct !DILexicalBlock(scope: !36, file: !1, line: 53, column: 2)
!144 = !DILocation(line: 53, column: 7, scope: !143)
!145 = !DILocation(line: 53, column: 14, scope: !146)
!146 = !DILexicalBlockFile(scope: !147, file: !1, discriminator: 1)
!147 = distinct !DILexicalBlock(scope: !143, file: !1, line: 53, column: 2)
!148 = !DILocation(line: 53, column: 16, scope: !146)
!149 = !DILocation(line: 53, column: 2, scope: !146)
!150 = !DILocation(line: 54, column: 18, scope: !151)
!151 = distinct !DILexicalBlock(scope: !147, file: !1, line: 53, column: 42)
!152 = !DILocation(line: 54, column: 3, scope: !151)
!153 = !DILocation(line: 54, column: 10, scope: !151)
!154 = !DILocation(line: 54, column: 21, scope: !151)
!155 = !DILocation(line: 54, column: 24, scope: !151)
!156 = !DILocation(line: 55, column: 18, scope: !151)
!157 = !DILocation(line: 55, column: 3, scope: !151)
!158 = !DILocation(line: 55, column: 10, scope: !151)
!159 = !DILocation(line: 55, column: 21, scope: !151)
!160 = !DILocation(line: 55, column: 29, scope: !151)
!161 = !DILocation(line: 56, column: 2, scope: !151)
!162 = !DILocation(line: 53, column: 37, scope: !163)
!163 = !DILexicalBlockFile(scope: !147, file: !1, discriminator: 2)
!164 = !DILocation(line: 53, column: 2, scope: !163)
!165 = !DILocation(line: 59, column: 2, scope: !36)
!166 = !DILocation(line: 59, column: 9, scope: !36)
!167 = !DILocation(line: 59, column: 17, scope: !36)
!168 = !DILocation(line: 63, column: 6, scope: !169)
!169 = distinct !DILexicalBlock(scope: !36, file: !1, line: 63, column: 6)
!170 = !DILocation(line: 63, column: 46, scope: !169)
!171 = !DILocation(line: 63, column: 53, scope: !169)
!172 = !DILocation(line: 63, column: 43, scope: !169)
!173 = !DILocation(line: 64, column: 4, scope: !169)
!174 = !DILocation(line: 64, column: 22, scope: !175)
!175 = !DILexicalBlockFile(scope: !169, file: !1, discriminator: 1)
!176 = !DILocation(line: 64, column: 29, scope: !175)
!177 = !DILocation(line: 64, column: 36, scope: !175)
!178 = !DILocation(line: 63, column: 6, scope: !179)
!179 = !DILexicalBlockFile(scope: !36, file: !1, discriminator: 1)
!180 = !DILocation(line: 65, column: 3, scope: !169)
!181 = !DILocation(line: 68, column: 12, scope: !36)
!182 = !DILocation(line: 68, column: 19, scope: !36)
!183 = !DILocation(line: 68, column: 31, scope: !36)
!184 = !DILocation(line: 68, column: 10, scope: !36)
!185 = !DILocation(line: 71, column: 17, scope: !186)
!186 = distinct !DILexicalBlock(scope: !36, file: !1, line: 71, column: 6)
!187 = !DILocation(line: 71, column: 21, scope: !186)
!188 = !DILocation(line: 71, column: 6, scope: !186)
!189 = !DILocation(line: 71, column: 55, scope: !186)
!190 = !DILocation(line: 71, column: 60, scope: !186)
!191 = !DILocation(line: 71, column: 58, scope: !186)
!192 = !DILocation(line: 71, column: 36, scope: !193)
!193 = !DILexicalBlockFile(scope: !186, file: !1, discriminator: 1)
!194 = !DILocation(line: 71, column: 33, scope: !186)
!195 = !DILocation(line: 71, column: 6, scope: !36)
!196 = !DILocation(line: 72, column: 3, scope: !186)
!197 = !DILocation(line: 75, column: 6, scope: !198)
!198 = distinct !DILexicalBlock(scope: !36, file: !1, line: 75, column: 6)
!199 = !DILocation(line: 75, column: 12, scope: !198)
!200 = !DILocation(line: 75, column: 6, scope: !36)
!201 = !DILocation(line: 76, column: 3, scope: !198)
!202 = !DILocation(line: 79, column: 6, scope: !203)
!203 = distinct !DILexicalBlock(scope: !36, file: !1, line: 79, column: 6)
!204 = !DILocation(line: 79, column: 12, scope: !203)
!205 = !DILocation(line: 79, column: 6, scope: !36)
!206 = !DILocation(line: 80, column: 3, scope: !207)
!207 = distinct !DILexicalBlock(scope: !203, file: !1, line: 79, column: 20)
!208 = !DILocalVariable(name: "ret_", scope: !209, file: !1, line: 80, type: !210)
!209 = distinct !DILexicalBlock(scope: !207, file: !1, line: 80, column: 3)
!210 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !39)
!211 = !DILocation(line: 80, column: 3, scope: !209)
!212 = !DILocation(line: 80, column: 3, scope: !213)
!213 = !DILexicalBlockFile(scope: !209, file: !1, discriminator: 1)
!214 = !DILocation(line: 80, column: 3, scope: !215)
!215 = !DILexicalBlockFile(scope: !216, file: !1, discriminator: 2)
!216 = distinct !DILexicalBlock(scope: !209, file: !1, line: 80, column: 3)
!217 = !DILocation(line: 80, column: 3, scope: !218)
!218 = !DILexicalBlockFile(scope: !209, file: !1, discriminator: 3)
!219 = !DILocation(line: 85, column: 32, scope: !220)
!220 = distinct !DILexicalBlock(scope: !207, file: !1, line: 85, column: 7)
!221 = !DILocation(line: 85, column: 7, scope: !220)
!222 = !DILocation(line: 85, column: 39, scope: !220)
!223 = !DILocation(line: 85, column: 7, scope: !207)
!224 = !DILocation(line: 86, column: 4, scope: !220)
!225 = !DILocation(line: 87, column: 2, scope: !207)
!226 = !DILocation(line: 88, column: 3, scope: !227)
!227 = distinct !DILexicalBlock(scope: !203, file: !1, line: 87, column: 9)
!228 = !DILocation(line: 88, column: 10, scope: !227)
!229 = !DILocation(line: 88, column: 26, scope: !227)
!230 = !DILocation(line: 92, column: 6, scope: !231)
!231 = distinct !DILexicalBlock(scope: !36, file: !1, line: 92, column: 6)
!232 = !DILocation(line: 92, column: 12, scope: !231)
!233 = !DILocation(line: 92, column: 6, scope: !36)
!234 = !DILocation(line: 93, column: 3, scope: !231)
!235 = !DILocalVariable(name: "ret_", scope: !236, file: !1, line: 93, type: !210)
!236 = distinct !DILexicalBlock(scope: !231, file: !1, line: 93, column: 3)
!237 = !DILocation(line: 93, column: 3, scope: !236)
!238 = !DILocation(line: 93, column: 3, scope: !239)
!239 = !DILexicalBlockFile(scope: !236, file: !1, discriminator: 1)
!240 = !DILocation(line: 93, column: 3, scope: !241)
!241 = !DILexicalBlockFile(scope: !242, file: !1, discriminator: 2)
!242 = distinct !DILexicalBlock(scope: !236, file: !1, line: 93, column: 3)
!243 = !DILocation(line: 93, column: 3, scope: !244)
!244 = !DILexicalBlockFile(scope: !236, file: !1, discriminator: 3)
!245 = !DILocation(line: 93, column: 3, scope: !246)
!246 = !DILexicalBlockFile(scope: !236, file: !1, discriminator: 4)
!247 = !DILocation(line: 96, column: 3, scope: !231)
!248 = !DILocation(line: 96, column: 10, scope: !231)
!249 = !DILocation(line: 96, column: 28, scope: !231)
!250 = !DILocation(line: 99, column: 9, scope: !251)
!251 = distinct !DILexicalBlock(scope: !36, file: !1, line: 99, column: 2)
!252 = !DILocation(line: 99, column: 7, scope: !251)
!253 = !DILocation(line: 99, column: 14, scope: !254)
!254 = !DILexicalBlockFile(scope: !255, file: !1, discriminator: 1)
!255 = distinct !DILexicalBlock(scope: !251, file: !1, line: 99, column: 2)
!256 = !DILocation(line: 99, column: 18, scope: !254)
!257 = !DILocation(line: 99, column: 16, scope: !254)
!258 = !DILocation(line: 99, column: 2, scope: !254)
!259 = !DILocalVariable(name: "ret", scope: !260, file: !1, line: 100, type: !210)
!260 = distinct !DILexicalBlock(scope: !255, file: !1, line: 99, column: 37)
!261 = !DILocation(line: 100, column: 18, scope: !260)
!262 = !DILocation(line: 101, column: 21, scope: !260)
!263 = !DILocation(line: 101, column: 6, scope: !260)
!264 = !DILocation(line: 101, column: 13, scope: !260)
!265 = !DILocation(line: 101, column: 25, scope: !260)
!266 = !DILocation(line: 102, column: 5, scope: !260)
!267 = !DILocation(line: 102, column: 18, scope: !260)
!268 = !DILocation(line: 100, column: 24, scope: !260)
!269 = !DILocation(line: 103, column: 7, scope: !270)
!270 = distinct !DILexicalBlock(scope: !260, file: !1, line: 103, column: 7)
!271 = !DILocation(line: 103, column: 11, scope: !270)
!272 = !DILocation(line: 103, column: 7, scope: !260)
!273 = !DILocation(line: 104, column: 20, scope: !274)
!274 = distinct !DILexicalBlock(scope: !270, file: !1, line: 103, column: 23)
!275 = !DILocation(line: 104, column: 27, scope: !274)
!276 = !DILocation(line: 104, column: 4, scope: !274)
!277 = !DILocation(line: 105, column: 11, scope: !274)
!278 = !DILocation(line: 105, column: 4, scope: !274)
!279 = !DILocation(line: 107, column: 2, scope: !260)
!280 = !DILocation(line: 99, column: 32, scope: !281)
!281 = !DILexicalBlockFile(scope: !255, file: !1, discriminator: 2)
!282 = !DILocation(line: 99, column: 2, scope: !281)
!283 = !DILocation(line: 110, column: 2, scope: !36)
!284 = !DILocation(line: 110, column: 9, scope: !179)
!285 = !DILocation(line: 110, column: 18, scope: !179)
!286 = !DILocation(line: 110, column: 16, scope: !179)
!287 = !DILocation(line: 110, column: 2, scope: !179)
!288 = !DILocation(line: 111, column: 16, scope: !289)
!289 = distinct !DILexicalBlock(scope: !290, file: !1, line: 111, column: 7)
!290 = distinct !DILexicalBlock(scope: !36, file: !1, line: 110, column: 27)
!291 = !DILocation(line: 111, column: 7, scope: !289)
!292 = !DILocation(line: 111, column: 20, scope: !289)
!293 = !DILocation(line: 111, column: 7, scope: !290)
!294 = !DILocation(line: 112, column: 20, scope: !295)
!295 = distinct !DILexicalBlock(scope: !289, file: !1, line: 111, column: 29)
!296 = !DILocation(line: 112, column: 27, scope: !295)
!297 = !DILocation(line: 112, column: 4, scope: !295)
!298 = !DILocation(line: 116, column: 4, scope: !295)
!299 = !DILocation(line: 110, column: 2, scope: !300)
!300 = !DILexicalBlockFile(scope: !36, file: !1, discriminator: 2)
!301 = !DILocation(line: 120, column: 2, scope: !36)
!302 = !DILocation(line: 121, column: 1, scope: !36)
!303 = !DILocalVariable(name: "buf", arg: 1, scope: !112, file: !113, line: 209, type: !109)
!304 = !DILocation(line: 209, column: 25, scope: !112)
!305 = !DILocalVariable(name: "num", scope: !112, file: !113, line: 211, type: !30)
!306 = !DILocation(line: 211, column: 11, scope: !112)
!307 = !DILocation(line: 211, column: 36, scope: !112)
!308 = !DILocation(line: 211, column: 17, scope: !112)
!309 = !DILocation(line: 212, column: 9, scope: !112)
!310 = !DILocation(line: 212, column: 2, scope: !112)
!311 = !DILocalVariable(name: "block", arg: 1, scope: !116, file: !1, line: 18, type: !40)
!312 = !DILocation(line: 18, column: 29, scope: !116)
!313 = !DILocalVariable(name: "allocator", arg: 2, scope: !116, file: !1, line: 18, type: !94)
!314 = !DILocation(line: 18, column: 52, scope: !116)
!315 = !DILocalVariable(name: "i", scope: !116, file: !1, line: 20, type: !102)
!316 = !DILocation(line: 20, column: 9, scope: !116)
!317 = !DILocation(line: 25, column: 9, scope: !318)
!318 = distinct !DILexicalBlock(scope: !116, file: !1, line: 25, column: 2)
!319 = !DILocation(line: 25, column: 7, scope: !318)
!320 = !DILocation(line: 25, column: 14, scope: !321)
!321 = !DILexicalBlockFile(scope: !322, file: !1, discriminator: 1)
!322 = distinct !DILexicalBlock(scope: !318, file: !1, line: 25, column: 2)
!323 = !DILocation(line: 25, column: 16, scope: !321)
!324 = !DILocation(line: 25, column: 2, scope: !321)
!325 = !DILocation(line: 26, column: 28, scope: !326)
!326 = distinct !DILexicalBlock(scope: !322, file: !1, line: 25, column: 41)
!327 = !DILocation(line: 26, column: 13, scope: !326)
!328 = !DILocation(line: 26, column: 20, scope: !326)
!329 = !DILocation(line: 26, column: 31, scope: !326)
!330 = !DILocation(line: 26, column: 40, scope: !326)
!331 = !DILocation(line: 26, column: 3, scope: !326)
!332 = !DILocation(line: 27, column: 18, scope: !326)
!333 = !DILocation(line: 27, column: 3, scope: !326)
!334 = !DILocation(line: 27, column: 10, scope: !326)
!335 = !DILocation(line: 27, column: 21, scope: !326)
!336 = !DILocation(line: 27, column: 24, scope: !326)
!337 = !DILocation(line: 28, column: 18, scope: !326)
!338 = !DILocation(line: 28, column: 3, scope: !326)
!339 = !DILocation(line: 28, column: 10, scope: !326)
!340 = !DILocation(line: 28, column: 21, scope: !326)
!341 = !DILocation(line: 28, column: 29, scope: !326)
!342 = !DILocation(line: 29, column: 2, scope: !326)
!343 = !DILocation(line: 25, column: 36, scope: !344)
!344 = !DILexicalBlockFile(scope: !322, file: !1, discriminator: 2)
!345 = !DILocation(line: 25, column: 2, scope: !344)
!346 = !DILocation(line: 31, column: 2, scope: !116)
