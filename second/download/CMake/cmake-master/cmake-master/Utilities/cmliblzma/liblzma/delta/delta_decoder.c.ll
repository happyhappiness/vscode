; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/delta/delta_decoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type { %struct.lzma_next_coder_s, i64, i8, [256 x i8] }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_filter_info_s = type { i64, {}*, i8* }
%struct.lzma_options_delta = type { i32, i32, i32, i32, i32, i32, i8*, i8* }

@.str = private unnamed_addr constant [31 x i8] c"coder->next.code != ((void*)0)\00", align 1
@.str.1 = private unnamed_addr constant [84 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/delta/delta_decoder.c\00", align 1
@__PRETTY_FUNCTION__.delta_decode = private unnamed_addr constant [163 x i8] c"lzma_ret delta_decode(lzma_coder *, lzma_allocator *, const uint8_t *restrict, size_t *restrict, size_t, uint8_t *restrict, size_t *restrict, size_t, lzma_action)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_delta_decoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter_info_s* %filters) #0 !dbg !38 {
entry:
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters.addr = alloca %struct.lzma_filter_info_s*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !149, metadata !150), !dbg !151
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !152, metadata !150), !dbg !153
  store %struct.lzma_filter_info_s* %filters, %struct.lzma_filter_info_s** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_info_s** %filters.addr, metadata !154, metadata !150), !dbg !155
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !156
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %0, i32 0, i32 3, !dbg !157
  store i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* @delta_decode, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !158
  %1 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !159
  %2 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !160
  %3 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !161
  %call = call i32 @lzma_delta_coder_init(%struct.lzma_next_coder_s* %1, %struct.lzma_allocator* %2, %struct.lzma_filter_info_s* %3), !dbg !162
  ret i32 %call, !dbg !163
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i32 @delta_decode(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, i8* noalias %in, i64* noalias %in_pos, i64 %in_size, i8* noalias %out, i64* noalias %out_pos, i64 %out_size, i32 %action) #0 !dbg !142 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %in.addr = alloca i8*, align 8
  %in_pos.addr = alloca i64*, align 8
  %in_size.addr = alloca i64, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %action.addr = alloca i32, align 4
  %out_start = alloca i64, align 8
  %ret = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !164, metadata !150), !dbg !165
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !166, metadata !150), !dbg !167
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !168, metadata !150), !dbg !169
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !170, metadata !150), !dbg !171
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !172, metadata !150), !dbg !173
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !174, metadata !150), !dbg !175
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !176, metadata !150), !dbg !177
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !178, metadata !150), !dbg !179
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !180, metadata !150), !dbg !181
  call void @llvm.dbg.declare(metadata i64* %out_start, metadata !182, metadata !150), !dbg !184
  %0 = load i64*, i64** %out_pos.addr, align 8, !dbg !185
  %1 = load i64, i64* %0, align 8, !dbg !186
  store i64 %1, i64* %out_start, align 8, !dbg !184
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !187, metadata !150), !dbg !188
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !189
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 0, !dbg !189
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 3, !dbg !189
  %3 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !189
  %cmp = icmp ne i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* %3, null, !dbg !189
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !189

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !190

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([84 x i8], [84 x i8]* @.str.1, i32 0, i32 0), i32 39, i8* getelementptr inbounds ([163 x i8], [163 x i8]* @__PRETTY_FUNCTION__.delta_decode, i32 0, i32 0)) #4, !dbg !192
  unreachable, !dbg !192
                                                  ; No predecessors!
  br label %cond.end, !dbg !194

cond.end:                                         ; preds = %4, %cond.true
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !196
  %next1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 0, !dbg !197
  %code2 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next1, i32 0, i32 3, !dbg !198
  %6 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code2, align 8, !dbg !198
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !199
  %next3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 0, !dbg !200
  %coder4 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next3, i32 0, i32 0, !dbg !201
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder4, align 8, !dbg !201
  %9 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !202
  %10 = load i8*, i8** %in.addr, align 8, !dbg !203
  %11 = load i64*, i64** %in_pos.addr, align 8, !dbg !204
  %12 = load i64, i64* %in_size.addr, align 8, !dbg !205
  %13 = load i8*, i8** %out.addr, align 8, !dbg !206
  %14 = load i64*, i64** %out_pos.addr, align 8, !dbg !207
  %15 = load i64, i64* %out_size.addr, align 8, !dbg !208
  %16 = load i32, i32* %action.addr, align 4, !dbg !209
  %call = call i32 %6(%struct.lzma_coder_s* %8, %struct.lzma_allocator* %9, i8* %10, i64* %11, i64 %12, i8* %13, i64* %14, i64 %15, i32 %16), !dbg !196
  store i32 %call, i32* %ret, align 4, !dbg !210
  %17 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !211
  %18 = load i8*, i8** %out.addr, align 8, !dbg !212
  %19 = load i64, i64* %out_start, align 8, !dbg !213
  %add.ptr = getelementptr inbounds i8, i8* %18, i64 %19, !dbg !214
  %20 = load i64*, i64** %out_pos.addr, align 8, !dbg !215
  %21 = load i64, i64* %20, align 8, !dbg !216
  %22 = load i64, i64* %out_start, align 8, !dbg !217
  %sub = sub i64 %21, %22, !dbg !218
  call void @decode_buffer(%struct.lzma_coder_s* %17, i8* %add.ptr, i64 %sub), !dbg !219
  %23 = load i32, i32* %ret, align 4, !dbg !220
  ret i32 %23, !dbg !221
}

declare i32 @lzma_delta_coder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #2

; Function Attrs: nounwind uwtable
define i32 @lzma_delta_props_decode(i8** %options, %struct.lzma_allocator* %allocator, i8* %props, i64 %props_size) #0 !dbg !138 {
entry:
  %retval = alloca i32, align 4
  %options.addr = alloca i8**, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %props.addr = alloca i8*, align 8
  %props_size.addr = alloca i64, align 8
  %opt = alloca %struct.lzma_options_delta*, align 8
  store i8** %options, i8*** %options.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %options.addr, metadata !222, metadata !150), !dbg !223
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !224, metadata !150), !dbg !225
  store i8* %props, i8** %props.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %props.addr, metadata !226, metadata !150), !dbg !227
  store i64 %props_size, i64* %props_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %props_size.addr, metadata !228, metadata !150), !dbg !229
  call void @llvm.dbg.declare(metadata %struct.lzma_options_delta** %opt, metadata !230, metadata !150), !dbg !246
  %0 = load i64, i64* %props_size.addr, align 8, !dbg !247
  %cmp = icmp ne i64 %0, 1, !dbg !249
  br i1 %cmp, label %if.then, label %if.end, !dbg !250

if.then:                                          ; preds = %entry
  store i32 8, i32* %retval, align 4, !dbg !251
  br label %return, !dbg !251

if.end:                                           ; preds = %entry
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !252
  %call = call noalias i8* @lzma_alloc(i64 40, %struct.lzma_allocator* %1), !dbg !253
  %2 = bitcast i8* %call to %struct.lzma_options_delta*, !dbg !253
  store %struct.lzma_options_delta* %2, %struct.lzma_options_delta** %opt, align 8, !dbg !254
  %3 = load %struct.lzma_options_delta*, %struct.lzma_options_delta** %opt, align 8, !dbg !255
  %cmp1 = icmp eq %struct.lzma_options_delta* %3, null, !dbg !257
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !258

if.then2:                                         ; preds = %if.end
  store i32 5, i32* %retval, align 4, !dbg !259
  br label %return, !dbg !259

if.end3:                                          ; preds = %if.end
  %4 = load %struct.lzma_options_delta*, %struct.lzma_options_delta** %opt, align 8, !dbg !260
  %type = getelementptr inbounds %struct.lzma_options_delta, %struct.lzma_options_delta* %4, i32 0, i32 0, !dbg !261
  store i32 0, i32* %type, align 8, !dbg !262
  %5 = load i8*, i8** %props.addr, align 8, !dbg !263
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 0, !dbg !263
  %6 = load i8, i8* %arrayidx, align 1, !dbg !263
  %conv = zext i8 %6 to i32, !dbg !263
  %add = add nsw i32 %conv, 1, !dbg !264
  %7 = load %struct.lzma_options_delta*, %struct.lzma_options_delta** %opt, align 8, !dbg !265
  %dist = getelementptr inbounds %struct.lzma_options_delta, %struct.lzma_options_delta* %7, i32 0, i32 1, !dbg !266
  store i32 %add, i32* %dist, align 4, !dbg !267
  %8 = load %struct.lzma_options_delta*, %struct.lzma_options_delta** %opt, align 8, !dbg !268
  %9 = bitcast %struct.lzma_options_delta* %8 to i8*, !dbg !268
  %10 = load i8**, i8*** %options.addr, align 8, !dbg !269
  store i8* %9, i8** %10, align 8, !dbg !270
  store i32 0, i32* %retval, align 4, !dbg !271
  br label %return, !dbg !271

return:                                           ; preds = %if.end3, %if.then2, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !272
  ret i32 %11, !dbg !272
}

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #3

; Function Attrs: nounwind uwtable
define internal void @decode_buffer(%struct.lzma_coder_s* %coder, i8* %buffer, i64 %size) #0 !dbg !143 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %buffer.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %i = alloca i64, align 8
  %distance = alloca i64, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !273, metadata !150), !dbg !274
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !275, metadata !150), !dbg !276
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !277, metadata !150), !dbg !278
  call void @llvm.dbg.declare(metadata i64* %i, metadata !279, metadata !150), !dbg !280
  call void @llvm.dbg.declare(metadata i64* %distance, metadata !281, metadata !150), !dbg !282
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !283
  %distance1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 1, !dbg !284
  %1 = load i64, i64* %distance1, align 8, !dbg !284
  store i64 %1, i64* %distance, align 8, !dbg !282
  store i64 0, i64* %i, align 8, !dbg !285
  br label %for.cond, !dbg !287

for.cond:                                         ; preds = %for.inc, %entry
  %2 = load i64, i64* %i, align 8, !dbg !288
  %3 = load i64, i64* %size.addr, align 8, !dbg !291
  %cmp = icmp ult i64 %2, %3, !dbg !292
  br i1 %cmp, label %for.body, label %for.end, !dbg !293

for.body:                                         ; preds = %for.cond
  %4 = load i64, i64* %distance, align 8, !dbg !294
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !296
  %pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 2, !dbg !297
  %6 = load i8, i8* %pos, align 8, !dbg !297
  %conv = zext i8 %6 to i64, !dbg !296
  %add = add i64 %4, %conv, !dbg !298
  %and = and i64 %add, 255, !dbg !299
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !300
  %history = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 3, !dbg !301
  %arrayidx = getelementptr inbounds [256 x i8], [256 x i8]* %history, i64 0, i64 %and, !dbg !300
  %8 = load i8, i8* %arrayidx, align 1, !dbg !300
  %conv2 = zext i8 %8 to i32, !dbg !300
  %9 = load i64, i64* %i, align 8, !dbg !302
  %10 = load i8*, i8** %buffer.addr, align 8, !dbg !303
  %arrayidx3 = getelementptr inbounds i8, i8* %10, i64 %9, !dbg !303
  %11 = load i8, i8* %arrayidx3, align 1, !dbg !304
  %conv4 = zext i8 %11 to i32, !dbg !304
  %add5 = add nsw i32 %conv4, %conv2, !dbg !304
  %conv6 = trunc i32 %add5 to i8, !dbg !304
  store i8 %conv6, i8* %arrayidx3, align 1, !dbg !304
  %12 = load i64, i64* %i, align 8, !dbg !305
  %13 = load i8*, i8** %buffer.addr, align 8, !dbg !306
  %arrayidx7 = getelementptr inbounds i8, i8* %13, i64 %12, !dbg !306
  %14 = load i8, i8* %arrayidx7, align 1, !dbg !306
  %15 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !307
  %pos8 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %15, i32 0, i32 2, !dbg !308
  %16 = load i8, i8* %pos8, align 8, !dbg !309
  %dec = add i8 %16, -1, !dbg !309
  store i8 %dec, i8* %pos8, align 8, !dbg !309
  %conv9 = zext i8 %16 to i32, !dbg !307
  %and10 = and i32 %conv9, 255, !dbg !310
  %idxprom = sext i32 %and10 to i64, !dbg !311
  %17 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !311
  %history11 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %17, i32 0, i32 3, !dbg !312
  %arrayidx12 = getelementptr inbounds [256 x i8], [256 x i8]* %history11, i64 0, i64 %idxprom, !dbg !311
  store i8 %14, i8* %arrayidx12, align 1, !dbg !313
  br label %for.inc, !dbg !314

for.inc:                                          ; preds = %for.body
  %18 = load i64, i64* %i, align 8, !dbg !315
  %inc = add i64 %18, 1, !dbg !315
  store i64 %inc, i64* %i, align 8, !dbg !315
  br label %for.cond, !dbg !317

for.end:                                          ; preds = %for.cond
  ret void, !dbg !318
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!146, !147}
!llvm.ident = !{!148}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !35, subprograms: !37)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/delta/delta_decoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !24, !31}
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
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !19)
!19 = !{!20, !21, !22, !23}
!20 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!21 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!22 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!23 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!24 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !25, line: 27, size: 32, align: 32, elements: !26)
!25 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!26 = !{!27, !28, !29, !30}
!27 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!28 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!29 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!30 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!31 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !32, line: 35, size: 32, align: 32, elements: !33)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/delta.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!33 = !{!34}
!34 = !DIEnumerator(name: "LZMA_DELTA_TYPE_BYTE", value: 0)
!35 = !{!36}
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!37 = !{!38, !138, !142, !143}
!38 = distinct !DISubprogram(name: "lzma_delta_decoder_init", scope: !1, file: !1, line: 52, type: !39, isLocal: false, isDefinition: true, scopeLine: 54, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!39 = !DISubroutineType(types: !40)
!40 = !{!41, !42, !77, !127}
!41 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!42 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!43 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !44, line: 75, baseType: !45)
!44 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!45 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !44, line: 119, size: 512, align: 64, elements: !46)
!46 = !{!47, !66, !70, !72, !98, !103, !110, !115}
!47 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !45, file: !44, line: 121, baseType: !48, size: 64, align: 64)
!48 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !49, size: 64, align: 64)
!49 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !44, line: 73, baseType: !50)
!50 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !51, line: 18, size: 2688, align: 64, elements: !52)
!51 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/delta/delta_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!52 = !{!53, !54, !58, !62}
!53 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !50, file: !51, line: 20, baseType: !43, size: 512, align: 64)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "distance", scope: !50, file: !51, line: 23, baseType: !55, size: 64, align: 64, offset: 512)
!55 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !56, line: 62, baseType: !57)
!56 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!57 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "pos", scope: !50, file: !51, line: 26, baseType: !59, size: 8, align: 8, offset: 576)
!59 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !60, line: 48, baseType: !61)
!60 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!61 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "history", scope: !50, file: !51, line: 29, baseType: !63, size: 2048, align: 8, offset: 584)
!63 = !DICompositeType(tag: DW_TAG_array_type, baseType: !59, size: 2048, align: 8, elements: !64)
!64 = !{!65}
!65 = !DISubrange(count: 256)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !45, file: !44, line: 125, baseType: !67, size: 64, align: 64, offset: 64)
!67 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !68, line: 63, baseType: !69)
!68 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!69 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !60, line: 55, baseType: !57)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !45, file: !44, line: 131, baseType: !71, size: 64, align: 64, offset: 128)
!71 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !60, line: 122, baseType: !57)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !45, file: !44, line: 134, baseType: !73, size: 64, align: 64, offset: 192)
!73 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !44, line: 89, baseType: !74)
!74 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !75, size: 64, align: 64)
!75 = !DISubroutineType(types: !76)
!76 = !{!41, !48, !77, !90, !93, !55, !95, !93, !55, !97}
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !79)
!79 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !80)
!80 = !{!81, !85, !89}
!81 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !79, file: !4, line: 376, baseType: !82, size: 64, align: 64)
!82 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !83, size: 64, align: 64)
!83 = !DISubroutineType(types: !84)
!84 = !{!36, !36, !55, !55}
!85 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !79, file: !4, line: 390, baseType: !86, size: 64, align: 64, offset: 64)
!86 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !87, size: 64, align: 64)
!87 = !DISubroutineType(types: !88)
!88 = !{null, !36, !36}
!89 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !79, file: !4, line: 401, baseType: !36, size: 64, align: 64, offset: 128)
!90 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !91)
!91 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !92, size: 64, align: 64)
!92 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !59)
!93 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !94)
!94 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !96)
!96 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !59, size: 64, align: 64)
!97 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !18)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !45, file: !44, line: 139, baseType: !99, size: 64, align: 64, offset: 256)
!99 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !44, line: 97, baseType: !100)
!100 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !101, size: 64, align: 64)
!101 = !DISubroutineType(types: !102)
!102 = !{null, !48, !77}
!103 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !45, file: !44, line: 143, baseType: !104, size: 64, align: 64, offset: 320)
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !105, size: 64, align: 64)
!105 = !DISubroutineType(types: !106)
!106 = !{!107, !108}
!107 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !25, line: 55, baseType: !24)
!108 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !109, size: 64, align: 64)
!109 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !49)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !45, file: !44, line: 147, baseType: !111, size: 64, align: 64, offset: 384)
!111 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !112, size: 64, align: 64)
!112 = !DISubroutineType(types: !113)
!113 = !{!41, !48, !114, !114, !69}
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !69, size: 64, align: 64)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !45, file: !44, line: 152, baseType: !116, size: 64, align: 64, offset: 448)
!116 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !117, size: 64, align: 64)
!117 = !DISubroutineType(types: !118)
!118 = !{!41, !48, !77, !119, !119}
!119 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !120, size: 64, align: 64)
!120 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !121)
!121 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !122, line: 65, baseType: !123)
!122 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!123 = !DICompositeType(tag: DW_TAG_structure_type, file: !122, line: 43, size: 128, align: 64, elements: !124)
!124 = !{!125, !126}
!125 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !123, file: !122, line: 54, baseType: !67, size: 64, align: 64)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !123, file: !122, line: 63, baseType: !36, size: 64, align: 64, offset: 64)
!127 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !128, size: 64, align: 64)
!128 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !129)
!129 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_info", file: !44, line: 77, baseType: !130)
!130 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_filter_info_s", file: !44, line: 104, size: 192, align: 64, elements: !131)
!131 = !{!132, !133, !136}
!132 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !130, file: !44, line: 107, baseType: !67, size: 64, align: 64)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !130, file: !44, line: 111, baseType: !134, size: 64, align: 64, offset: 64)
!134 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_init_function", file: !44, line: 81, baseType: !135)
!135 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !39, size: 64, align: 64)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !130, file: !44, line: 114, baseType: !36, size: 64, align: 64, offset: 128)
!137 = !{}
!138 = distinct !DISubprogram(name: "lzma_delta_props_decode", scope: !1, file: !1, line: 61, type: !139, isLocal: false, isDefinition: true, scopeLine: 63, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!139 = !DISubroutineType(types: !140)
!140 = !{!41, !141, !77, !91, !55}
!141 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!142 = distinct !DISubprogram(name: "delta_decode", scope: !1, file: !1, line: 31, type: !75, isLocal: true, isDefinition: true, scopeLine: 35, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!143 = distinct !DISubprogram(name: "decode_buffer", scope: !1, file: !1, line: 18, type: !144, isLocal: true, isDefinition: true, scopeLine: 19, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!144 = !DISubroutineType(types: !145)
!145 = !{null, !48, !96, !55}
!146 = !{i32 2, !"Dwarf Version", i32 4}
!147 = !{i32 2, !"Debug Info Version", i32 3}
!148 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!149 = !DILocalVariable(name: "next", arg: 1, scope: !38, file: !1, line: 52, type: !42)
!150 = !DIExpression()
!151 = !DILocation(line: 52, column: 42, scope: !38)
!152 = !DILocalVariable(name: "allocator", arg: 2, scope: !38, file: !1, line: 52, type: !77)
!153 = !DILocation(line: 52, column: 64, scope: !38)
!154 = !DILocalVariable(name: "filters", arg: 3, scope: !38, file: !1, line: 53, type: !127)
!155 = !DILocation(line: 53, column: 27, scope: !38)
!156 = !DILocation(line: 55, column: 2, scope: !38)
!157 = !DILocation(line: 55, column: 8, scope: !38)
!158 = !DILocation(line: 55, column: 13, scope: !38)
!159 = !DILocation(line: 56, column: 31, scope: !38)
!160 = !DILocation(line: 56, column: 37, scope: !38)
!161 = !DILocation(line: 56, column: 48, scope: !38)
!162 = !DILocation(line: 56, column: 9, scope: !38)
!163 = !DILocation(line: 56, column: 2, scope: !38)
!164 = !DILocalVariable(name: "coder", arg: 1, scope: !142, file: !1, line: 31, type: !48)
!165 = !DILocation(line: 31, column: 26, scope: !142)
!166 = !DILocalVariable(name: "allocator", arg: 2, scope: !142, file: !1, line: 31, type: !77)
!167 = !DILocation(line: 31, column: 49, scope: !142)
!168 = !DILocalVariable(name: "in", arg: 3, scope: !142, file: !1, line: 32, type: !90)
!169 = !DILocation(line: 32, column: 32, scope: !142)
!170 = !DILocalVariable(name: "in_pos", arg: 4, scope: !142, file: !1, line: 32, type: !93)
!171 = !DILocation(line: 32, column: 58, scope: !142)
!172 = !DILocalVariable(name: "in_size", arg: 5, scope: !142, file: !1, line: 33, type: !55)
!173 = !DILocation(line: 33, column: 10, scope: !142)
!174 = !DILocalVariable(name: "out", arg: 6, scope: !142, file: !1, line: 33, type: !95)
!175 = !DILocation(line: 33, column: 42, scope: !142)
!176 = !DILocalVariable(name: "out_pos", arg: 7, scope: !142, file: !1, line: 34, type: !93)
!177 = !DILocation(line: 34, column: 25, scope: !142)
!178 = !DILocalVariable(name: "out_size", arg: 8, scope: !142, file: !1, line: 34, type: !55)
!179 = !DILocation(line: 34, column: 41, scope: !142)
!180 = !DILocalVariable(name: "action", arg: 9, scope: !142, file: !1, line: 34, type: !97)
!181 = !DILocation(line: 34, column: 63, scope: !142)
!182 = !DILocalVariable(name: "out_start", scope: !142, file: !1, line: 36, type: !183)
!183 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !55)
!184 = !DILocation(line: 36, column: 15, scope: !142)
!185 = !DILocation(line: 36, column: 28, scope: !142)
!186 = !DILocation(line: 36, column: 27, scope: !142)
!187 = !DILocalVariable(name: "ret", scope: !142, file: !1, line: 37, type: !41)
!188 = !DILocation(line: 37, column: 11, scope: !142)
!189 = !DILocation(line: 39, column: 2, scope: !142)
!190 = !DILocation(line: 39, column: 2, scope: !191)
!191 = !DILexicalBlockFile(scope: !142, file: !1, discriminator: 1)
!192 = !DILocation(line: 39, column: 2, scope: !193)
!193 = !DILexicalBlockFile(scope: !142, file: !1, discriminator: 2)
!194 = !DILocation(line: 39, column: 2, scope: !195)
!195 = !DILexicalBlockFile(scope: !142, file: !1, discriminator: 3)
!196 = !DILocation(line: 41, column: 8, scope: !142)
!197 = !DILocation(line: 41, column: 15, scope: !142)
!198 = !DILocation(line: 41, column: 20, scope: !142)
!199 = !DILocation(line: 41, column: 25, scope: !142)
!200 = !DILocation(line: 41, column: 32, scope: !142)
!201 = !DILocation(line: 41, column: 37, scope: !142)
!202 = !DILocation(line: 41, column: 44, scope: !142)
!203 = !DILocation(line: 42, column: 4, scope: !142)
!204 = !DILocation(line: 42, column: 8, scope: !142)
!205 = !DILocation(line: 42, column: 16, scope: !142)
!206 = !DILocation(line: 42, column: 25, scope: !142)
!207 = !DILocation(line: 42, column: 30, scope: !142)
!208 = !DILocation(line: 42, column: 39, scope: !142)
!209 = !DILocation(line: 43, column: 4, scope: !142)
!210 = !DILocation(line: 41, column: 6, scope: !142)
!211 = !DILocation(line: 45, column: 16, scope: !142)
!212 = !DILocation(line: 45, column: 23, scope: !142)
!213 = !DILocation(line: 45, column: 29, scope: !142)
!214 = !DILocation(line: 45, column: 27, scope: !142)
!215 = !DILocation(line: 45, column: 41, scope: !142)
!216 = !DILocation(line: 45, column: 40, scope: !142)
!217 = !DILocation(line: 45, column: 51, scope: !142)
!218 = !DILocation(line: 45, column: 49, scope: !142)
!219 = !DILocation(line: 45, column: 2, scope: !142)
!220 = !DILocation(line: 47, column: 9, scope: !142)
!221 = !DILocation(line: 47, column: 2, scope: !142)
!222 = !DILocalVariable(name: "options", arg: 1, scope: !138, file: !1, line: 61, type: !141)
!223 = !DILocation(line: 61, column: 32, scope: !138)
!224 = !DILocalVariable(name: "allocator", arg: 2, scope: !138, file: !1, line: 61, type: !77)
!225 = !DILocation(line: 61, column: 57, scope: !138)
!226 = !DILocalVariable(name: "props", arg: 3, scope: !138, file: !1, line: 62, type: !91)
!227 = !DILocation(line: 62, column: 18, scope: !138)
!228 = !DILocalVariable(name: "props_size", arg: 4, scope: !138, file: !1, line: 62, type: !55)
!229 = !DILocation(line: 62, column: 32, scope: !138)
!230 = !DILocalVariable(name: "opt", scope: !138, file: !1, line: 64, type: !231)
!231 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !232, size: 64, align: 64)
!232 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_delta", file: !32, line: 77, baseType: !233)
!233 = !DICompositeType(tag: DW_TAG_structure_type, file: !32, line: 45, size: 320, align: 64, elements: !234)
!234 = !{!235, !237, !240, !241, !242, !243, !244, !245}
!235 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !233, file: !32, line: 47, baseType: !236, size: 32, align: 32)
!236 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_delta_type", file: !32, line: 37, baseType: !31)
!237 = !DIDerivedType(tag: DW_TAG_member, name: "dist", scope: !233, file: !32, line: 59, baseType: !238, size: 32, align: 32, offset: 32)
!238 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !60, line: 51, baseType: !239)
!239 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!240 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !233, file: !32, line: 70, baseType: !238, size: 32, align: 32, offset: 64)
!241 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !233, file: !32, line: 71, baseType: !238, size: 32, align: 32, offset: 96)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !233, file: !32, line: 72, baseType: !238, size: 32, align: 32, offset: 128)
!243 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !233, file: !32, line: 73, baseType: !238, size: 32, align: 32, offset: 160)
!244 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !233, file: !32, line: 74, baseType: !36, size: 64, align: 64, offset: 192)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !233, file: !32, line: 75, baseType: !36, size: 64, align: 64, offset: 256)
!246 = !DILocation(line: 64, column: 22, scope: !138)
!247 = !DILocation(line: 66, column: 6, scope: !248)
!248 = distinct !DILexicalBlock(scope: !138, file: !1, line: 66, column: 6)
!249 = !DILocation(line: 66, column: 17, scope: !248)
!250 = !DILocation(line: 66, column: 6, scope: !138)
!251 = !DILocation(line: 67, column: 3, scope: !248)
!252 = !DILocation(line: 69, column: 47, scope: !138)
!253 = !DILocation(line: 69, column: 8, scope: !138)
!254 = !DILocation(line: 69, column: 6, scope: !138)
!255 = !DILocation(line: 70, column: 6, scope: !256)
!256 = distinct !DILexicalBlock(scope: !138, file: !1, line: 70, column: 6)
!257 = !DILocation(line: 70, column: 10, scope: !256)
!258 = !DILocation(line: 70, column: 6, scope: !138)
!259 = !DILocation(line: 71, column: 3, scope: !256)
!260 = !DILocation(line: 73, column: 2, scope: !138)
!261 = !DILocation(line: 73, column: 7, scope: !138)
!262 = !DILocation(line: 73, column: 12, scope: !138)
!263 = !DILocation(line: 74, column: 14, scope: !138)
!264 = !DILocation(line: 74, column: 23, scope: !138)
!265 = !DILocation(line: 74, column: 2, scope: !138)
!266 = !DILocation(line: 74, column: 7, scope: !138)
!267 = !DILocation(line: 74, column: 12, scope: !138)
!268 = !DILocation(line: 76, column: 13, scope: !138)
!269 = !DILocation(line: 76, column: 3, scope: !138)
!270 = !DILocation(line: 76, column: 11, scope: !138)
!271 = !DILocation(line: 78, column: 2, scope: !138)
!272 = !DILocation(line: 79, column: 1, scope: !138)
!273 = !DILocalVariable(name: "coder", arg: 1, scope: !143, file: !1, line: 18, type: !48)
!274 = !DILocation(line: 18, column: 27, scope: !143)
!275 = !DILocalVariable(name: "buffer", arg: 2, scope: !143, file: !1, line: 18, type: !96)
!276 = !DILocation(line: 18, column: 43, scope: !143)
!277 = !DILocalVariable(name: "size", arg: 3, scope: !143, file: !1, line: 18, type: !55)
!278 = !DILocation(line: 18, column: 58, scope: !143)
!279 = !DILocalVariable(name: "i", scope: !143, file: !1, line: 20, type: !55)
!280 = !DILocation(line: 20, column: 9, scope: !143)
!281 = !DILocalVariable(name: "distance", scope: !143, file: !1, line: 21, type: !183)
!282 = !DILocation(line: 21, column: 15, scope: !143)
!283 = !DILocation(line: 21, column: 26, scope: !143)
!284 = !DILocation(line: 21, column: 33, scope: !143)
!285 = !DILocation(line: 23, column: 9, scope: !286)
!286 = distinct !DILexicalBlock(scope: !143, file: !1, line: 23, column: 2)
!287 = !DILocation(line: 23, column: 7, scope: !286)
!288 = !DILocation(line: 23, column: 14, scope: !289)
!289 = !DILexicalBlockFile(scope: !290, file: !1, discriminator: 1)
!290 = distinct !DILexicalBlock(scope: !286, file: !1, line: 23, column: 2)
!291 = !DILocation(line: 23, column: 18, scope: !289)
!292 = !DILocation(line: 23, column: 16, scope: !289)
!293 = !DILocation(line: 23, column: 2, scope: !289)
!294 = !DILocation(line: 24, column: 32, scope: !295)
!295 = distinct !DILexicalBlock(scope: !290, file: !1, line: 23, column: 29)
!296 = !DILocation(line: 24, column: 43, scope: !295)
!297 = !DILocation(line: 24, column: 50, scope: !295)
!298 = !DILocation(line: 24, column: 41, scope: !295)
!299 = !DILocation(line: 24, column: 55, scope: !295)
!300 = !DILocation(line: 24, column: 16, scope: !295)
!301 = !DILocation(line: 24, column: 23, scope: !295)
!302 = !DILocation(line: 24, column: 10, scope: !295)
!303 = !DILocation(line: 24, column: 3, scope: !295)
!304 = !DILocation(line: 24, column: 13, scope: !295)
!305 = !DILocation(line: 25, column: 48, scope: !295)
!306 = !DILocation(line: 25, column: 41, scope: !295)
!307 = !DILocation(line: 25, column: 18, scope: !295)
!308 = !DILocation(line: 25, column: 25, scope: !295)
!309 = !DILocation(line: 25, column: 28, scope: !295)
!310 = !DILocation(line: 25, column: 31, scope: !295)
!311 = !DILocation(line: 25, column: 3, scope: !295)
!312 = !DILocation(line: 25, column: 10, scope: !295)
!313 = !DILocation(line: 25, column: 39, scope: !295)
!314 = !DILocation(line: 26, column: 2, scope: !295)
!315 = !DILocation(line: 23, column: 24, scope: !316)
!316 = !DILexicalBlockFile(scope: !290, file: !1, discriminator: 2)
!317 = !DILocation(line: 23, column: 2, scope: !316)
!318 = !DILocation(line: 27, column: 1, scope: !143)
