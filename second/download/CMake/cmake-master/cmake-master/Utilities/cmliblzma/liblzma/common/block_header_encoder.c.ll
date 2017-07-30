; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/block_header_encoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_block = type { i32, i32, i32, i64, i64, %struct.lzma_filter*, [64 x i8], i8*, i8*, i8*, i32, i32, i64, i64, i64, i64, i64, i64, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8, i8, i8 }
%struct.lzma_filter = type { i64, i8* }

; Function Attrs: nounwind uwtable
define i32 @lzma_block_header_size(%struct.lzma_block* %block) #0 !dbg !35 {
entry:
  %retval = alloca i32, align 4
  %block.addr = alloca %struct.lzma_block*, align 8
  %i = alloca i64, align 8
  %size = alloca i32, align 4
  %add = alloca i32, align 4
  %add13 = alloca i32, align 4
  %add31 = alloca i32, align 4
  %ret_ = alloca i32, align 4
  store %struct.lzma_block* %block, %struct.lzma_block** %block.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_block** %block.addr, metadata !107, metadata !108), !dbg !109
  call void @llvm.dbg.declare(metadata i64* %i, metadata !110, metadata !108), !dbg !113
  call void @llvm.dbg.declare(metadata i32* %size, metadata !114, metadata !108), !dbg !115
  store i32 6, i32* %size, align 4, !dbg !115
  %0 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !116
  %version = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %0, i32 0, i32 0, !dbg !118
  %1 = load i32, i32* %version, align 8, !dbg !118
  %cmp = icmp ne i32 %1, 0, !dbg !119
  br i1 %cmp, label %if.then, label %if.end, !dbg !120

if.then:                                          ; preds = %entry
  store i32 8, i32* %retval, align 4, !dbg !121
  br label %return, !dbg !121

if.end:                                           ; preds = %entry
  %2 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !122
  %compressed_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %2, i32 0, i32 3, !dbg !124
  %3 = load i64, i64* %compressed_size, align 8, !dbg !124
  %cmp1 = icmp ne i64 %3, -1, !dbg !125
  br i1 %cmp1, label %if.then2, label %if.end10, !dbg !126

if.then2:                                         ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %add, metadata !127, metadata !108), !dbg !130
  %4 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !131
  %compressed_size3 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %4, i32 0, i32 3, !dbg !132
  %5 = load i64, i64* %compressed_size3, align 8, !dbg !132
  %call = call i32 @lzma_vli_size(i64 %5) #6, !dbg !133
  store i32 %call, i32* %add, align 4, !dbg !130
  %6 = load i32, i32* %add, align 4, !dbg !134
  %cmp4 = icmp eq i32 %6, 0, !dbg !136
  br i1 %cmp4, label %if.then7, label %lor.lhs.false, !dbg !137

lor.lhs.false:                                    ; preds = %if.then2
  %7 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !138
  %compressed_size5 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %7, i32 0, i32 3, !dbg !140
  %8 = load i64, i64* %compressed_size5, align 8, !dbg !140
  %cmp6 = icmp eq i64 %8, 0, !dbg !141
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !142

if.then7:                                         ; preds = %lor.lhs.false, %if.then2
  store i32 11, i32* %retval, align 4, !dbg !143
  br label %return, !dbg !143

if.end8:                                          ; preds = %lor.lhs.false
  %9 = load i32, i32* %add, align 4, !dbg !144
  %10 = load i32, i32* %size, align 4, !dbg !145
  %add9 = add i32 %10, %9, !dbg !145
  store i32 %add9, i32* %size, align 4, !dbg !145
  br label %if.end10, !dbg !146

if.end10:                                         ; preds = %if.end8, %if.end
  %11 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !147
  %uncompressed_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %11, i32 0, i32 4, !dbg !149
  %12 = load i64, i64* %uncompressed_size, align 8, !dbg !149
  %cmp11 = icmp ne i64 %12, -1, !dbg !150
  br i1 %cmp11, label %if.then12, label %if.end20, !dbg !151

if.then12:                                        ; preds = %if.end10
  call void @llvm.dbg.declare(metadata i32* %add13, metadata !152, metadata !108), !dbg !154
  %13 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !155
  %uncompressed_size14 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %13, i32 0, i32 4, !dbg !156
  %14 = load i64, i64* %uncompressed_size14, align 8, !dbg !156
  %call15 = call i32 @lzma_vli_size(i64 %14) #6, !dbg !157
  store i32 %call15, i32* %add13, align 4, !dbg !154
  %15 = load i32, i32* %add13, align 4, !dbg !158
  %cmp16 = icmp eq i32 %15, 0, !dbg !160
  br i1 %cmp16, label %if.then17, label %if.end18, !dbg !161

if.then17:                                        ; preds = %if.then12
  store i32 11, i32* %retval, align 4, !dbg !162
  br label %return, !dbg !162

if.end18:                                         ; preds = %if.then12
  %16 = load i32, i32* %add13, align 4, !dbg !163
  %17 = load i32, i32* %size, align 4, !dbg !164
  %add19 = add i32 %17, %16, !dbg !164
  store i32 %add19, i32* %size, align 4, !dbg !164
  br label %if.end20, !dbg !165

if.end20:                                         ; preds = %if.end18, %if.end10
  %18 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !166
  %filters = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %18, i32 0, i32 5, !dbg !168
  %19 = load %struct.lzma_filter*, %struct.lzma_filter** %filters, align 8, !dbg !168
  %cmp21 = icmp eq %struct.lzma_filter* %19, null, !dbg !169
  br i1 %cmp21, label %if.then25, label %lor.lhs.false22, !dbg !170

lor.lhs.false22:                                  ; preds = %if.end20
  %20 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !171
  %filters23 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %20, i32 0, i32 5, !dbg !173
  %21 = load %struct.lzma_filter*, %struct.lzma_filter** %filters23, align 8, !dbg !173
  %arrayidx = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %21, i64 0, !dbg !171
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx, i32 0, i32 0, !dbg !174
  %22 = load i64, i64* %id, align 8, !dbg !174
  %cmp24 = icmp eq i64 %22, -1, !dbg !175
  br i1 %cmp24, label %if.then25, label %if.end26, !dbg !176

if.then25:                                        ; preds = %lor.lhs.false22, %if.end20
  store i32 11, i32* %retval, align 4, !dbg !177
  br label %return, !dbg !177

if.end26:                                         ; preds = %lor.lhs.false22
  store i64 0, i64* %i, align 8, !dbg !178
  br label %for.cond, !dbg !180

for.cond:                                         ; preds = %for.inc, %if.end26
  %23 = load i64, i64* %i, align 8, !dbg !181
  %24 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !184
  %filters27 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %24, i32 0, i32 5, !dbg !185
  %25 = load %struct.lzma_filter*, %struct.lzma_filter** %filters27, align 8, !dbg !185
  %arrayidx28 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %25, i64 %23, !dbg !184
  %id29 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx28, i32 0, i32 0, !dbg !186
  %26 = load i64, i64* %id29, align 8, !dbg !186
  %cmp30 = icmp ne i64 %26, -1, !dbg !187
  br i1 %cmp30, label %for.body, label %for.end, !dbg !188

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i32* %add31, metadata !189, metadata !108), !dbg !191
  %27 = load i64, i64* %i, align 8, !dbg !192
  %cmp32 = icmp eq i64 %27, 4, !dbg !194
  br i1 %cmp32, label %if.then33, label %if.end34, !dbg !195

if.then33:                                        ; preds = %for.body
  store i32 11, i32* %retval, align 4, !dbg !196
  br label %return, !dbg !196

if.end34:                                         ; preds = %for.body
  br label %do.body, !dbg !197

do.body:                                          ; preds = %if.end34
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !198, metadata !108), !dbg !201
  %28 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !202
  %filters35 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %28, i32 0, i32 5, !dbg !202
  %29 = load %struct.lzma_filter*, %struct.lzma_filter** %filters35, align 8, !dbg !202
  %30 = load i64, i64* %i, align 8, !dbg !202
  %add.ptr = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %29, i64 %30, !dbg !202
  %call36 = call i32 @lzma_filter_flags_size(i32* %add31, %struct.lzma_filter* %add.ptr) #7, !dbg !202
  store i32 %call36, i32* %ret_, align 4, !dbg !202
  %31 = load i32, i32* %ret_, align 4, !dbg !202
  %cmp37 = icmp ne i32 %31, 0, !dbg !202
  br i1 %cmp37, label %if.then38, label %if.end39, !dbg !202

if.then38:                                        ; preds = %do.body
  %32 = load i32, i32* %ret_, align 4, !dbg !204
  store i32 %32, i32* %retval, align 4, !dbg !204
  br label %return, !dbg !204

if.end39:                                         ; preds = %do.body
  br label %do.end, !dbg !207

do.end:                                           ; preds = %if.end39
  %33 = load i32, i32* %add31, align 4, !dbg !209
  %34 = load i32, i32* %size, align 4, !dbg !210
  %add40 = add i32 %34, %33, !dbg !210
  store i32 %add40, i32* %size, align 4, !dbg !210
  br label %for.inc, !dbg !211

for.inc:                                          ; preds = %do.end
  %35 = load i64, i64* %i, align 8, !dbg !212
  %inc = add i64 %35, 1, !dbg !212
  store i64 %inc, i64* %i, align 8, !dbg !212
  br label %for.cond, !dbg !214

for.end:                                          ; preds = %for.cond
  %36 = load i32, i32* %size, align 4, !dbg !215
  %add41 = add i32 %36, 3, !dbg !216
  %and = and i32 %add41, -4, !dbg !217
  %37 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !218
  %header_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %37, i32 0, i32 1, !dbg !219
  store i32 %and, i32* %header_size, align 4, !dbg !220
  store i32 0, i32* %retval, align 4, !dbg !221
  br label %return, !dbg !221

return:                                           ; preds = %for.end, %if.then38, %if.then33, %if.then25, %if.then17, %if.then7, %if.then
  %38 = load i32, i32* %retval, align 4, !dbg !222
  ret i32 %38, !dbg !222
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind readonly
declare i32 @lzma_vli_size(i64) #2

; Function Attrs: nounwind
declare i32 @lzma_filter_flags_size(i32*, %struct.lzma_filter*) #3

; Function Attrs: nounwind uwtable
define i32 @lzma_block_header_encode(%struct.lzma_block* %block, i8* %out) #0 !dbg !94 {
entry:
  %retval = alloca i32, align 4
  %block.addr = alloca %struct.lzma_block*, align 8
  %out.addr = alloca i8*, align 8
  %out_size = alloca i64, align 8
  %out_pos = alloca i64, align 8
  %filter_count = alloca i64, align 8
  %ret_ = alloca i32, align 4
  %ret_25 = alloca i32, align 4
  %ret_53 = alloca i32, align 4
  store %struct.lzma_block* %block, %struct.lzma_block** %block.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_block** %block.addr, metadata !223, metadata !108), !dbg !224
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !225, metadata !108), !dbg !226
  call void @llvm.dbg.declare(metadata i64* %out_size, metadata !227, metadata !108), !dbg !228
  call void @llvm.dbg.declare(metadata i64* %out_pos, metadata !229, metadata !108), !dbg !230
  store i64 2, i64* %out_pos, align 8, !dbg !230
  call void @llvm.dbg.declare(metadata i64* %filter_count, metadata !231, metadata !108), !dbg !232
  store i64 0, i64* %filter_count, align 8, !dbg !232
  %0 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !233
  %call = call i64 @lzma_block_unpadded_size(%struct.lzma_block* %0) #6, !dbg !235
  %cmp = icmp eq i64 %call, 0, !dbg !236
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !237

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !238
  %uncompressed_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %1, i32 0, i32 4, !dbg !238
  %2 = load i64, i64* %uncompressed_size, align 8, !dbg !238
  %cmp1 = icmp ule i64 %2, 9223372036854775807, !dbg !238
  br i1 %cmp1, label %if.end, label %lor.lhs.false2, !dbg !238

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %3 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !240
  %uncompressed_size3 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %3, i32 0, i32 4, !dbg !240
  %4 = load i64, i64* %uncompressed_size3, align 8, !dbg !240
  %cmp4 = icmp eq i64 %4, -1, !dbg !240
  br i1 %cmp4, label %if.end, label %if.then, !dbg !242

if.then:                                          ; preds = %lor.lhs.false2, %entry
  store i32 11, i32* %retval, align 4, !dbg !244
  br label %return, !dbg !244

if.end:                                           ; preds = %lor.lhs.false2, %lor.lhs.false
  %5 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !245
  %header_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %5, i32 0, i32 1, !dbg !246
  %6 = load i32, i32* %header_size, align 4, !dbg !246
  %sub = sub i32 %6, 4, !dbg !247
  %conv = zext i32 %sub to i64, !dbg !245
  store i64 %conv, i64* %out_size, align 8, !dbg !248
  %7 = load i64, i64* %out_size, align 8, !dbg !249
  %div = udiv i64 %7, 4, !dbg !250
  %conv5 = trunc i64 %div to i8, !dbg !249
  %8 = load i8*, i8** %out.addr, align 8, !dbg !251
  %arrayidx = getelementptr inbounds i8, i8* %8, i64 0, !dbg !251
  store i8 %conv5, i8* %arrayidx, align 1, !dbg !252
  %9 = load i8*, i8** %out.addr, align 8, !dbg !253
  %arrayidx6 = getelementptr inbounds i8, i8* %9, i64 1, !dbg !253
  store i8 0, i8* %arrayidx6, align 1, !dbg !254
  %10 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !255
  %compressed_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %10, i32 0, i32 3, !dbg !257
  %11 = load i64, i64* %compressed_size, align 8, !dbg !257
  %cmp7 = icmp ne i64 %11, -1, !dbg !258
  br i1 %cmp7, label %if.then9, label %if.end19, !dbg !259

if.then9:                                         ; preds = %if.end
  br label %do.body, !dbg !260

do.body:                                          ; preds = %if.then9
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !262, metadata !108), !dbg !264
  %12 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !265
  %compressed_size10 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %12, i32 0, i32 3, !dbg !265
  %13 = load i64, i64* %compressed_size10, align 8, !dbg !265
  %14 = load i8*, i8** %out.addr, align 8, !dbg !265
  %15 = load i64, i64* %out_size, align 8, !dbg !265
  %call11 = call i32 @lzma_vli_encode(i64 %13, i64* null, i8* %14, i64* %out_pos, i64 %15) #7, !dbg !265
  store i32 %call11, i32* %ret_, align 4, !dbg !265
  %16 = load i32, i32* %ret_, align 4, !dbg !265
  %cmp12 = icmp ne i32 %16, 0, !dbg !265
  br i1 %cmp12, label %if.then14, label %if.end15, !dbg !265

if.then14:                                        ; preds = %do.body
  %17 = load i32, i32* %ret_, align 4, !dbg !267
  store i32 %17, i32* %retval, align 4, !dbg !267
  br label %return, !dbg !267

if.end15:                                         ; preds = %do.body
  br label %do.end, !dbg !270

do.end:                                           ; preds = %if.end15
  %18 = load i8*, i8** %out.addr, align 8, !dbg !272
  %arrayidx16 = getelementptr inbounds i8, i8* %18, i64 1, !dbg !272
  %19 = load i8, i8* %arrayidx16, align 1, !dbg !273
  %conv17 = zext i8 %19 to i32, !dbg !273
  %or = or i32 %conv17, 64, !dbg !273
  %conv18 = trunc i32 %or to i8, !dbg !273
  store i8 %conv18, i8* %arrayidx16, align 1, !dbg !273
  br label %if.end19, !dbg !274

if.end19:                                         ; preds = %do.end, %if.end
  %20 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !275
  %uncompressed_size20 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %20, i32 0, i32 4, !dbg !277
  %21 = load i64, i64* %uncompressed_size20, align 8, !dbg !277
  %cmp21 = icmp ne i64 %21, -1, !dbg !278
  br i1 %cmp21, label %if.then23, label %if.end37, !dbg !279

if.then23:                                        ; preds = %if.end19
  br label %do.body24, !dbg !280

do.body24:                                        ; preds = %if.then23
  call void @llvm.dbg.declare(metadata i32* %ret_25, metadata !282, metadata !108), !dbg !284
  %22 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !285
  %uncompressed_size26 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %22, i32 0, i32 4, !dbg !285
  %23 = load i64, i64* %uncompressed_size26, align 8, !dbg !285
  %24 = load i8*, i8** %out.addr, align 8, !dbg !285
  %25 = load i64, i64* %out_size, align 8, !dbg !285
  %call27 = call i32 @lzma_vli_encode(i64 %23, i64* null, i8* %24, i64* %out_pos, i64 %25) #7, !dbg !285
  store i32 %call27, i32* %ret_25, align 4, !dbg !285
  %26 = load i32, i32* %ret_25, align 4, !dbg !285
  %cmp28 = icmp ne i32 %26, 0, !dbg !285
  br i1 %cmp28, label %if.then30, label %if.end31, !dbg !285

if.then30:                                        ; preds = %do.body24
  %27 = load i32, i32* %ret_25, align 4, !dbg !287
  store i32 %27, i32* %retval, align 4, !dbg !287
  br label %return, !dbg !287

if.end31:                                         ; preds = %do.body24
  br label %do.end32, !dbg !290

do.end32:                                         ; preds = %if.end31
  %28 = load i8*, i8** %out.addr, align 8, !dbg !292
  %arrayidx33 = getelementptr inbounds i8, i8* %28, i64 1, !dbg !292
  %29 = load i8, i8* %arrayidx33, align 1, !dbg !293
  %conv34 = zext i8 %29 to i32, !dbg !293
  %or35 = or i32 %conv34, 128, !dbg !293
  %conv36 = trunc i32 %or35 to i8, !dbg !293
  store i8 %conv36, i8* %arrayidx33, align 1, !dbg !293
  br label %if.end37, !dbg !294

if.end37:                                         ; preds = %do.end32, %if.end19
  %30 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !295
  %filters = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %30, i32 0, i32 5, !dbg !297
  %31 = load %struct.lzma_filter*, %struct.lzma_filter** %filters, align 8, !dbg !297
  %cmp38 = icmp eq %struct.lzma_filter* %31, null, !dbg !298
  br i1 %cmp38, label %if.then45, label %lor.lhs.false40, !dbg !299

lor.lhs.false40:                                  ; preds = %if.end37
  %32 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !300
  %filters41 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %32, i32 0, i32 5, !dbg !302
  %33 = load %struct.lzma_filter*, %struct.lzma_filter** %filters41, align 8, !dbg !302
  %arrayidx42 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %33, i64 0, !dbg !300
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx42, i32 0, i32 0, !dbg !303
  %34 = load i64, i64* %id, align 8, !dbg !303
  %cmp43 = icmp eq i64 %34, -1, !dbg !304
  br i1 %cmp43, label %if.then45, label %if.end46, !dbg !305

if.then45:                                        ; preds = %lor.lhs.false40, %if.end37
  store i32 11, i32* %retval, align 4, !dbg !306
  br label %return, !dbg !306

if.end46:                                         ; preds = %lor.lhs.false40
  br label %do.body47, !dbg !307

do.body47:                                        ; preds = %do.cond, %if.end46
  %35 = load i64, i64* %filter_count, align 8, !dbg !308
  %cmp48 = icmp eq i64 %35, 4, !dbg !311
  br i1 %cmp48, label %if.then50, label %if.end51, !dbg !312

if.then50:                                        ; preds = %do.body47
  store i32 11, i32* %retval, align 4, !dbg !313
  br label %return, !dbg !313

if.end51:                                         ; preds = %do.body47
  br label %do.body52, !dbg !314

do.body52:                                        ; preds = %if.end51
  call void @llvm.dbg.declare(metadata i32* %ret_53, metadata !315, metadata !108), !dbg !317
  %36 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !318
  %filters54 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %36, i32 0, i32 5, !dbg !318
  %37 = load %struct.lzma_filter*, %struct.lzma_filter** %filters54, align 8, !dbg !318
  %38 = load i64, i64* %filter_count, align 8, !dbg !318
  %add.ptr = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %37, i64 %38, !dbg !318
  %39 = load i8*, i8** %out.addr, align 8, !dbg !318
  %40 = load i64, i64* %out_size, align 8, !dbg !318
  %call55 = call i32 @lzma_filter_flags_encode(%struct.lzma_filter* %add.ptr, i8* %39, i64* %out_pos, i64 %40) #7, !dbg !318
  store i32 %call55, i32* %ret_53, align 4, !dbg !318
  %41 = load i32, i32* %ret_53, align 4, !dbg !318
  %cmp56 = icmp ne i32 %41, 0, !dbg !318
  br i1 %cmp56, label %if.then58, label %if.end59, !dbg !318

if.then58:                                        ; preds = %do.body52
  %42 = load i32, i32* %ret_53, align 4, !dbg !320
  store i32 %42, i32* %retval, align 4, !dbg !320
  br label %return, !dbg !320

if.end59:                                         ; preds = %do.body52
  br label %do.end60, !dbg !323

do.end60:                                         ; preds = %if.end59
  br label %do.cond, !dbg !325

do.cond:                                          ; preds = %do.end60
  %43 = load i64, i64* %filter_count, align 8, !dbg !326
  %inc = add i64 %43, 1, !dbg !326
  store i64 %inc, i64* %filter_count, align 8, !dbg !326
  %44 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !327
  %filters61 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %44, i32 0, i32 5, !dbg !328
  %45 = load %struct.lzma_filter*, %struct.lzma_filter** %filters61, align 8, !dbg !328
  %arrayidx62 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %45, i64 %inc, !dbg !327
  %id63 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx62, i32 0, i32 0, !dbg !329
  %46 = load i64, i64* %id63, align 8, !dbg !329
  %cmp64 = icmp ne i64 %46, -1, !dbg !330
  br i1 %cmp64, label %do.body47, label %do.end66, !dbg !331

do.end66:                                         ; preds = %do.cond
  %47 = load i64, i64* %filter_count, align 8, !dbg !332
  %sub67 = sub i64 %47, 1, !dbg !333
  %48 = load i8*, i8** %out.addr, align 8, !dbg !334
  %arrayidx68 = getelementptr inbounds i8, i8* %48, i64 1, !dbg !334
  %49 = load i8, i8* %arrayidx68, align 1, !dbg !335
  %conv69 = zext i8 %49 to i64, !dbg !335
  %or70 = or i64 %conv69, %sub67, !dbg !335
  %conv71 = trunc i64 %or70 to i8, !dbg !335
  store i8 %conv71, i8* %arrayidx68, align 1, !dbg !335
  %50 = load i8*, i8** %out.addr, align 8, !dbg !336
  %51 = load i64, i64* %out_pos, align 8, !dbg !336
  %add.ptr72 = getelementptr inbounds i8, i8* %50, i64 %51, !dbg !336
  %52 = load i64, i64* %out_size, align 8, !dbg !336
  %53 = load i64, i64* %out_pos, align 8, !dbg !336
  %sub73 = sub i64 %52, %53, !dbg !336
  call void @llvm.memset.p0i8.i64(i8* %add.ptr72, i8 0, i64 %sub73, i32 1, i1 false), !dbg !336
  %54 = load i8*, i8** %out.addr, align 8, !dbg !337
  %55 = load i64, i64* %out_size, align 8, !dbg !337
  %add.ptr74 = getelementptr inbounds i8, i8* %54, i64 %55, !dbg !337
  %56 = load i8*, i8** %out.addr, align 8, !dbg !337
  %57 = load i64, i64* %out_size, align 8, !dbg !337
  %call75 = call i32 @lzma_crc32(i8* %56, i64 %57, i32 0) #6, !dbg !337
  call void @write32ne(i8* %add.ptr74, i32 %call75), !dbg !338
  store i32 0, i32* %retval, align 4, !dbg !339
  br label %return, !dbg !339

return:                                           ; preds = %do.end66, %if.then58, %if.then50, %if.then45, %if.then30, %if.then14, %if.then
  %58 = load i32, i32* %retval, align 4, !dbg !340
  ret i32 %58, !dbg !340
}

; Function Attrs: nounwind readonly
declare i64 @lzma_block_unpadded_size(%struct.lzma_block*) #2

; Function Attrs: nounwind
declare i32 @lzma_vli_encode(i64, i64*, i8*, i64*, i64) #3

; Function Attrs: nounwind
declare i32 @lzma_filter_flags_encode(%struct.lzma_filter*, i8*, i64*, i64) #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #4

; Function Attrs: inlinehint nounwind uwtable
define internal void @write32ne(i8* %buf, i32 %num) #5 !dbg !100 {
entry:
  %buf.addr = alloca i8*, align 8
  %num.addr = alloca i32, align 4
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !341, metadata !108), !dbg !342
  store i32 %num, i32* %num.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %num.addr, metadata !343, metadata !108), !dbg !344
  %0 = load i32, i32* %num.addr, align 4, !dbg !345
  %1 = load i8*, i8** %buf.addr, align 8, !dbg !346
  %2 = bitcast i8* %1 to i32*, !dbg !347
  store i32 %0, i32* %2, align 4, !dbg !348
  ret void, !dbg !349
}

; Function Attrs: nounwind readonly
declare i32 @lzma_crc32(i8*, i64, i32) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly }
attributes #7 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!104, !105}
!llvm.ident = !{!106}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !28, subprograms: !34)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/block_header_encoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
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
!28 = !{!29, !30, !33}
!29 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!30 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !31, line: 51, baseType: !32)
!31 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!32 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!33 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!34 = !{!35, !94, !100}
!35 = distinct !DISubprogram(name: "lzma_block_header_size", scope: !1, file: !1, line: 18, type: !36, isLocal: false, isDefinition: true, scopeLine: 19, flags: DIFlagPrototyped, isOptimized: false, variables: !93)
!36 = !DISubroutineType(types: !37)
!37 = !{!38, !39}
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!39 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !40, size: 64, align: 64)
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_block", file: !41, line: 245, baseType: !42)
!41 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/block.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!42 = !DICompositeType(tag: DW_TAG_structure_type, file: !41, line: 30, size: 1664, align: 64, elements: !43)
!43 = !{!44, !45, !46, !48, !53, !54, !62, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !81, !82, !83, !84, !86, !87, !88, !89, !90, !91, !92}
!44 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !42, file: !41, line: 47, baseType: !30, size: 32, align: 32)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "header_size", scope: !42, file: !41, line: 67, baseType: !30, size: 32, align: 32, offset: 32)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !42, file: !41, line: 88, baseType: !47, size: 32, align: 32, offset: 64)
!47 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !19, line: 55, baseType: !18)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_size", scope: !42, file: !41, line: 143, baseType: !49, size: 64, align: 64, offset: 128)
!49 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !50, line: 63, baseType: !51)
!50 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!51 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !31, line: 55, baseType: !52)
!52 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !42, file: !41, line: 167, baseType: !49, size: 64, align: 64, offset: 192)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "filters", scope: !42, file: !41, line: 195, baseType: !55, size: 64, align: 64, offset: 256)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !57, line: 65, baseType: !58)
!57 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!58 = !DICompositeType(tag: DW_TAG_structure_type, file: !57, line: 43, size: 128, align: 64, elements: !59)
!59 = !{!60, !61}
!60 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !58, file: !57, line: 54, baseType: !49, size: 64, align: 64)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !58, file: !57, line: 63, baseType: !29, size: 64, align: 64, offset: 64)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "raw_check", scope: !42, file: !41, line: 212, baseType: !63, size: 512, align: 8, offset: 320)
!63 = !DICompositeType(tag: DW_TAG_array_type, baseType: !64, size: 512, align: 8, elements: !66)
!64 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !31, line: 48, baseType: !65)
!65 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!66 = !{!67}
!67 = !DISubrange(count: 64)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !42, file: !41, line: 221, baseType: !29, size: 64, align: 64, offset: 832)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !42, file: !41, line: 222, baseType: !29, size: 64, align: 64, offset: 896)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !42, file: !41, line: 223, baseType: !29, size: 64, align: 64, offset: 960)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !42, file: !41, line: 224, baseType: !30, size: 32, align: 32, offset: 1024)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !42, file: !41, line: 225, baseType: !30, size: 32, align: 32, offset: 1056)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !42, file: !41, line: 226, baseType: !49, size: 64, align: 64, offset: 1088)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !42, file: !41, line: 227, baseType: !49, size: 64, align: 64, offset: 1152)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !42, file: !41, line: 228, baseType: !49, size: 64, align: 64, offset: 1216)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !42, file: !41, line: 229, baseType: !49, size: 64, align: 64, offset: 1280)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !42, file: !41, line: 230, baseType: !49, size: 64, align: 64, offset: 1344)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !42, file: !41, line: 231, baseType: !49, size: 64, align: 64, offset: 1408)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !42, file: !41, line: 232, baseType: !80, size: 32, align: 32, offset: 1472)
!80 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !25)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !42, file: !41, line: 233, baseType: !80, size: 32, align: 32, offset: 1504)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !42, file: !41, line: 234, baseType: !80, size: 32, align: 32, offset: 1536)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !42, file: !41, line: 235, baseType: !80, size: 32, align: 32, offset: 1568)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool1", scope: !42, file: !41, line: 236, baseType: !85, size: 8, align: 8, offset: 1600)
!85 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !4, line: 29, baseType: !65)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool2", scope: !42, file: !41, line: 237, baseType: !85, size: 8, align: 8, offset: 1608)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool3", scope: !42, file: !41, line: 238, baseType: !85, size: 8, align: 8, offset: 1616)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool4", scope: !42, file: !41, line: 239, baseType: !85, size: 8, align: 8, offset: 1624)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool5", scope: !42, file: !41, line: 240, baseType: !85, size: 8, align: 8, offset: 1632)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool6", scope: !42, file: !41, line: 241, baseType: !85, size: 8, align: 8, offset: 1640)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool7", scope: !42, file: !41, line: 242, baseType: !85, size: 8, align: 8, offset: 1648)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool8", scope: !42, file: !41, line: 243, baseType: !85, size: 8, align: 8, offset: 1656)
!93 = !{}
!94 = distinct !DISubprogram(name: "lzma_block_header_encode", scope: !1, file: !1, line: 77, type: !95, isLocal: false, isDefinition: true, scopeLine: 78, flags: DIFlagPrototyped, isOptimized: false, variables: !93)
!95 = !DISubroutineType(types: !96)
!96 = !{!38, !97, !99}
!97 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !98, size: 64, align: 64)
!98 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !40)
!99 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !64, size: 64, align: 64)
!100 = distinct !DISubprogram(name: "write32ne", scope: !101, file: !101, line: 255, type: !102, isLocal: true, isDefinition: true, scopeLine: 256, flags: DIFlagPrototyped, isOptimized: false, variables: !93)
!101 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/common/tuklib_integer.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!102 = !DISubroutineType(types: !103)
!103 = !{null, !99, !30}
!104 = !{i32 2, !"Dwarf Version", i32 4}
!105 = !{i32 2, !"Debug Info Version", i32 3}
!106 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!107 = !DILocalVariable(name: "block", arg: 1, scope: !35, file: !1, line: 18, type: !39)
!108 = !DIExpression()
!109 = !DILocation(line: 18, column: 36, scope: !35)
!110 = !DILocalVariable(name: "i", scope: !35, file: !1, line: 20, type: !111)
!111 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !112, line: 62, baseType: !52)
!112 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!113 = !DILocation(line: 20, column: 9, scope: !35)
!114 = !DILocalVariable(name: "size", scope: !35, file: !1, line: 23, type: !30)
!115 = !DILocation(line: 23, column: 11, scope: !35)
!116 = !DILocation(line: 25, column: 6, scope: !117)
!117 = distinct !DILexicalBlock(scope: !35, file: !1, line: 25, column: 6)
!118 = !DILocation(line: 25, column: 13, scope: !117)
!119 = !DILocation(line: 25, column: 21, scope: !117)
!120 = !DILocation(line: 25, column: 6, scope: !35)
!121 = !DILocation(line: 26, column: 3, scope: !117)
!122 = !DILocation(line: 29, column: 6, scope: !123)
!123 = distinct !DILexicalBlock(scope: !35, file: !1, line: 29, column: 6)
!124 = !DILocation(line: 29, column: 13, scope: !123)
!125 = !DILocation(line: 29, column: 29, scope: !123)
!126 = !DILocation(line: 29, column: 6, scope: !35)
!127 = !DILocalVariable(name: "add", scope: !128, file: !1, line: 30, type: !129)
!128 = distinct !DILexicalBlock(scope: !123, file: !1, line: 29, column: 50)
!129 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !30)
!130 = !DILocation(line: 30, column: 18, scope: !128)
!131 = !DILocation(line: 30, column: 38, scope: !128)
!132 = !DILocation(line: 30, column: 45, scope: !128)
!133 = !DILocation(line: 30, column: 24, scope: !128)
!134 = !DILocation(line: 31, column: 7, scope: !135)
!135 = distinct !DILexicalBlock(scope: !128, file: !1, line: 31, column: 7)
!136 = !DILocation(line: 31, column: 11, scope: !135)
!137 = !DILocation(line: 31, column: 16, scope: !135)
!138 = !DILocation(line: 31, column: 19, scope: !139)
!139 = !DILexicalBlockFile(scope: !135, file: !1, discriminator: 1)
!140 = !DILocation(line: 31, column: 26, scope: !139)
!141 = !DILocation(line: 31, column: 42, scope: !139)
!142 = !DILocation(line: 31, column: 7, scope: !139)
!143 = !DILocation(line: 32, column: 4, scope: !135)
!144 = !DILocation(line: 34, column: 11, scope: !128)
!145 = !DILocation(line: 34, column: 8, scope: !128)
!146 = !DILocation(line: 35, column: 2, scope: !128)
!147 = !DILocation(line: 38, column: 6, scope: !148)
!148 = distinct !DILexicalBlock(scope: !35, file: !1, line: 38, column: 6)
!149 = !DILocation(line: 38, column: 13, scope: !148)
!150 = !DILocation(line: 38, column: 31, scope: !148)
!151 = !DILocation(line: 38, column: 6, scope: !35)
!152 = !DILocalVariable(name: "add", scope: !153, file: !1, line: 39, type: !129)
!153 = distinct !DILexicalBlock(scope: !148, file: !1, line: 38, column: 52)
!154 = !DILocation(line: 39, column: 18, scope: !153)
!155 = !DILocation(line: 39, column: 38, scope: !153)
!156 = !DILocation(line: 39, column: 45, scope: !153)
!157 = !DILocation(line: 39, column: 24, scope: !153)
!158 = !DILocation(line: 40, column: 7, scope: !159)
!159 = distinct !DILexicalBlock(scope: !153, file: !1, line: 40, column: 7)
!160 = !DILocation(line: 40, column: 11, scope: !159)
!161 = !DILocation(line: 40, column: 7, scope: !153)
!162 = !DILocation(line: 41, column: 4, scope: !159)
!163 = !DILocation(line: 43, column: 11, scope: !153)
!164 = !DILocation(line: 43, column: 8, scope: !153)
!165 = !DILocation(line: 44, column: 2, scope: !153)
!166 = !DILocation(line: 47, column: 6, scope: !167)
!167 = distinct !DILexicalBlock(scope: !35, file: !1, line: 47, column: 6)
!168 = !DILocation(line: 47, column: 13, scope: !167)
!169 = !DILocation(line: 47, column: 21, scope: !167)
!170 = !DILocation(line: 47, column: 29, scope: !167)
!171 = !DILocation(line: 47, column: 32, scope: !172)
!172 = !DILexicalBlockFile(scope: !167, file: !1, discriminator: 1)
!173 = !DILocation(line: 47, column: 39, scope: !172)
!174 = !DILocation(line: 47, column: 50, scope: !172)
!175 = !DILocation(line: 47, column: 53, scope: !172)
!176 = !DILocation(line: 47, column: 6, scope: !172)
!177 = !DILocation(line: 48, column: 3, scope: !167)
!178 = !DILocation(line: 50, column: 9, scope: !179)
!179 = distinct !DILexicalBlock(scope: !35, file: !1, line: 50, column: 2)
!180 = !DILocation(line: 50, column: 7, scope: !179)
!181 = !DILocation(line: 50, column: 29, scope: !182)
!182 = !DILexicalBlockFile(scope: !183, file: !1, discriminator: 1)
!183 = distinct !DILexicalBlock(scope: !179, file: !1, line: 50, column: 2)
!184 = !DILocation(line: 50, column: 14, scope: !182)
!185 = !DILocation(line: 50, column: 21, scope: !182)
!186 = !DILocation(line: 50, column: 32, scope: !182)
!187 = !DILocation(line: 50, column: 35, scope: !182)
!188 = !DILocation(line: 50, column: 2, scope: !182)
!189 = !DILocalVariable(name: "add", scope: !190, file: !1, line: 51, type: !30)
!190 = distinct !DILexicalBlock(scope: !183, file: !1, line: 50, column: 61)
!191 = !DILocation(line: 51, column: 12, scope: !190)
!192 = !DILocation(line: 54, column: 7, scope: !193)
!193 = distinct !DILexicalBlock(scope: !190, file: !1, line: 54, column: 7)
!194 = !DILocation(line: 54, column: 9, scope: !193)
!195 = !DILocation(line: 54, column: 7, scope: !190)
!196 = !DILocation(line: 55, column: 4, scope: !193)
!197 = !DILocation(line: 57, column: 3, scope: !190)
!198 = !DILocalVariable(name: "ret_", scope: !199, file: !1, line: 57, type: !200)
!199 = distinct !DILexicalBlock(scope: !190, file: !1, line: 57, column: 3)
!200 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !38)
!201 = !DILocation(line: 57, column: 3, scope: !199)
!202 = !DILocation(line: 57, column: 3, scope: !203)
!203 = !DILexicalBlockFile(scope: !199, file: !1, discriminator: 1)
!204 = !DILocation(line: 57, column: 3, scope: !205)
!205 = !DILexicalBlockFile(scope: !206, file: !1, discriminator: 2)
!206 = distinct !DILexicalBlock(scope: !199, file: !1, line: 57, column: 3)
!207 = !DILocation(line: 57, column: 3, scope: !208)
!208 = !DILexicalBlockFile(scope: !199, file: !1, discriminator: 3)
!209 = !DILocation(line: 60, column: 11, scope: !190)
!210 = !DILocation(line: 60, column: 8, scope: !190)
!211 = !DILocation(line: 61, column: 2, scope: !190)
!212 = !DILocation(line: 50, column: 56, scope: !213)
!213 = !DILexicalBlockFile(scope: !183, file: !1, discriminator: 2)
!214 = !DILocation(line: 50, column: 2, scope: !213)
!215 = !DILocation(line: 64, column: 24, scope: !35)
!216 = !DILocation(line: 64, column: 29, scope: !35)
!217 = !DILocation(line: 64, column: 34, scope: !35)
!218 = !DILocation(line: 64, column: 2, scope: !35)
!219 = !DILocation(line: 64, column: 9, scope: !35)
!220 = !DILocation(line: 64, column: 21, scope: !35)
!221 = !DILocation(line: 72, column: 2, scope: !35)
!222 = !DILocation(line: 73, column: 1, scope: !35)
!223 = !DILocalVariable(name: "block", arg: 1, scope: !94, file: !1, line: 77, type: !97)
!224 = !DILocation(line: 77, column: 44, scope: !94)
!225 = !DILocalVariable(name: "out", arg: 2, scope: !94, file: !1, line: 77, type: !99)
!226 = !DILocation(line: 77, column: 60, scope: !94)
!227 = !DILocalVariable(name: "out_size", scope: !94, file: !1, line: 79, type: !111)
!228 = !DILocation(line: 79, column: 9, scope: !94)
!229 = !DILocalVariable(name: "out_pos", scope: !94, file: !1, line: 80, type: !111)
!230 = !DILocation(line: 80, column: 9, scope: !94)
!231 = !DILocalVariable(name: "filter_count", scope: !94, file: !1, line: 81, type: !111)
!232 = !DILocation(line: 81, column: 9, scope: !94)
!233 = !DILocation(line: 84, column: 31, scope: !234)
!234 = distinct !DILexicalBlock(scope: !94, file: !1, line: 84, column: 6)
!235 = !DILocation(line: 84, column: 6, scope: !234)
!236 = !DILocation(line: 84, column: 38, scope: !234)
!237 = !DILocation(line: 85, column: 4, scope: !234)
!238 = !DILocation(line: 85, column: 8, scope: !239)
!239 = !DILexicalBlockFile(scope: !234, file: !1, discriminator: 1)
!240 = !DILocation(line: 85, column: 8, scope: !241)
!241 = !DILexicalBlockFile(scope: !234, file: !1, discriminator: 2)
!242 = !DILocation(line: 84, column: 6, scope: !243)
!243 = !DILexicalBlockFile(scope: !94, file: !1, discriminator: 1)
!244 = !DILocation(line: 86, column: 3, scope: !234)
!245 = !DILocation(line: 89, column: 13, scope: !94)
!246 = !DILocation(line: 89, column: 20, scope: !94)
!247 = !DILocation(line: 89, column: 32, scope: !94)
!248 = !DILocation(line: 89, column: 11, scope: !94)
!249 = !DILocation(line: 92, column: 11, scope: !94)
!250 = !DILocation(line: 92, column: 20, scope: !94)
!251 = !DILocation(line: 92, column: 2, scope: !94)
!252 = !DILocation(line: 92, column: 9, scope: !94)
!253 = !DILocation(line: 95, column: 2, scope: !94)
!254 = !DILocation(line: 95, column: 9, scope: !94)
!255 = !DILocation(line: 98, column: 6, scope: !256)
!256 = distinct !DILexicalBlock(scope: !94, file: !1, line: 98, column: 6)
!257 = !DILocation(line: 98, column: 13, scope: !256)
!258 = !DILocation(line: 98, column: 29, scope: !256)
!259 = !DILocation(line: 98, column: 6, scope: !94)
!260 = !DILocation(line: 99, column: 3, scope: !261)
!261 = distinct !DILexicalBlock(scope: !256, file: !1, line: 98, column: 50)
!262 = !DILocalVariable(name: "ret_", scope: !263, file: !1, line: 99, type: !200)
!263 = distinct !DILexicalBlock(scope: !261, file: !1, line: 99, column: 3)
!264 = !DILocation(line: 99, column: 3, scope: !263)
!265 = !DILocation(line: 99, column: 3, scope: !266)
!266 = !DILexicalBlockFile(scope: !263, file: !1, discriminator: 1)
!267 = !DILocation(line: 99, column: 3, scope: !268)
!268 = !DILexicalBlockFile(scope: !269, file: !1, discriminator: 2)
!269 = distinct !DILexicalBlock(scope: !263, file: !1, line: 99, column: 3)
!270 = !DILocation(line: 99, column: 3, scope: !271)
!271 = !DILexicalBlockFile(scope: !263, file: !1, discriminator: 3)
!272 = !DILocation(line: 102, column: 3, scope: !261)
!273 = !DILocation(line: 102, column: 10, scope: !261)
!274 = !DILocation(line: 103, column: 2, scope: !261)
!275 = !DILocation(line: 106, column: 6, scope: !276)
!276 = distinct !DILexicalBlock(scope: !94, file: !1, line: 106, column: 6)
!277 = !DILocation(line: 106, column: 13, scope: !276)
!278 = !DILocation(line: 106, column: 31, scope: !276)
!279 = !DILocation(line: 106, column: 6, scope: !94)
!280 = !DILocation(line: 107, column: 3, scope: !281)
!281 = distinct !DILexicalBlock(scope: !276, file: !1, line: 106, column: 52)
!282 = !DILocalVariable(name: "ret_", scope: !283, file: !1, line: 107, type: !200)
!283 = distinct !DILexicalBlock(scope: !281, file: !1, line: 107, column: 3)
!284 = !DILocation(line: 107, column: 3, scope: !283)
!285 = !DILocation(line: 107, column: 3, scope: !286)
!286 = !DILexicalBlockFile(scope: !283, file: !1, discriminator: 1)
!287 = !DILocation(line: 107, column: 3, scope: !288)
!288 = !DILexicalBlockFile(scope: !289, file: !1, discriminator: 2)
!289 = distinct !DILexicalBlock(scope: !283, file: !1, line: 107, column: 3)
!290 = !DILocation(line: 107, column: 3, scope: !291)
!291 = !DILexicalBlockFile(scope: !283, file: !1, discriminator: 3)
!292 = !DILocation(line: 110, column: 3, scope: !281)
!293 = !DILocation(line: 110, column: 10, scope: !281)
!294 = !DILocation(line: 111, column: 2, scope: !281)
!295 = !DILocation(line: 114, column: 6, scope: !296)
!296 = distinct !DILexicalBlock(scope: !94, file: !1, line: 114, column: 6)
!297 = !DILocation(line: 114, column: 13, scope: !296)
!298 = !DILocation(line: 114, column: 21, scope: !296)
!299 = !DILocation(line: 114, column: 29, scope: !296)
!300 = !DILocation(line: 114, column: 32, scope: !301)
!301 = !DILexicalBlockFile(scope: !296, file: !1, discriminator: 1)
!302 = !DILocation(line: 114, column: 39, scope: !301)
!303 = !DILocation(line: 114, column: 50, scope: !301)
!304 = !DILocation(line: 114, column: 53, scope: !301)
!305 = !DILocation(line: 114, column: 6, scope: !301)
!306 = !DILocation(line: 115, column: 3, scope: !296)
!307 = !DILocation(line: 117, column: 2, scope: !94)
!308 = !DILocation(line: 119, column: 7, scope: !309)
!309 = distinct !DILexicalBlock(scope: !310, file: !1, line: 119, column: 7)
!310 = distinct !DILexicalBlock(scope: !94, file: !1, line: 117, column: 5)
!311 = !DILocation(line: 119, column: 20, scope: !309)
!312 = !DILocation(line: 119, column: 7, scope: !310)
!313 = !DILocation(line: 120, column: 4, scope: !309)
!314 = !DILocation(line: 122, column: 3, scope: !310)
!315 = !DILocalVariable(name: "ret_", scope: !316, file: !1, line: 122, type: !200)
!316 = distinct !DILexicalBlock(scope: !310, file: !1, line: 122, column: 3)
!317 = !DILocation(line: 122, column: 3, scope: !316)
!318 = !DILocation(line: 122, column: 3, scope: !319)
!319 = !DILexicalBlockFile(scope: !316, file: !1, discriminator: 1)
!320 = !DILocation(line: 122, column: 3, scope: !321)
!321 = !DILexicalBlockFile(scope: !322, file: !1, discriminator: 2)
!322 = distinct !DILexicalBlock(scope: !316, file: !1, line: 122, column: 3)
!323 = !DILocation(line: 122, column: 3, scope: !324)
!324 = !DILexicalBlockFile(scope: !316, file: !1, discriminator: 3)
!325 = !DILocation(line: 126, column: 2, scope: !310)
!326 = !DILocation(line: 126, column: 26, scope: !243)
!327 = !DILocation(line: 126, column: 11, scope: !243)
!328 = !DILocation(line: 126, column: 18, scope: !243)
!329 = !DILocation(line: 126, column: 42, scope: !243)
!330 = !DILocation(line: 126, column: 45, scope: !243)
!331 = !DILocation(line: 126, column: 2, scope: !243)
!332 = !DILocation(line: 128, column: 12, scope: !94)
!333 = !DILocation(line: 128, column: 25, scope: !94)
!334 = !DILocation(line: 128, column: 2, scope: !94)
!335 = !DILocation(line: 128, column: 9, scope: !94)
!336 = !DILocation(line: 131, column: 2, scope: !94)
!337 = !DILocation(line: 134, column: 2, scope: !94)
!338 = !DILocation(line: 134, column: 2, scope: !243)
!339 = !DILocation(line: 136, column: 2, scope: !94)
!340 = !DILocation(line: 137, column: 1, scope: !94)
!341 = !DILocalVariable(name: "buf", arg: 1, scope: !100, file: !101, line: 255, type: !99)
!342 = !DILocation(line: 255, column: 20, scope: !100)
!343 = !DILocalVariable(name: "num", arg: 2, scope: !100, file: !101, line: 255, type: !30)
!344 = !DILocation(line: 255, column: 34, scope: !100)
!345 = !DILocation(line: 257, column: 21, scope: !100)
!346 = !DILocation(line: 257, column: 15, scope: !100)
!347 = !DILocation(line: 257, column: 2, scope: !100)
!348 = !DILocation(line: 257, column: 19, scope: !100)
!349 = !DILocation(line: 258, column: 2, scope: !100)
