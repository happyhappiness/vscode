; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/block_util.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_block = type { i32, i32, i32, i64, i64, %struct.lzma_filter*, [64 x i8], i8*, i8*, i8*, i32, i32, i64, i64, i64, i64, i64, i64, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8, i8, i8 }
%struct.lzma_filter = type { i64, i8* }

@.str = private unnamed_addr constant [21 x i8] c"unpadded_size >= 5UL\00", align 1
@.str.1 = private unnamed_addr constant [82 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/block_util.c\00", align 1
@__PRETTY_FUNCTION__.lzma_block_unpadded_size = private unnamed_addr constant [54 x i8] c"lzma_vli lzma_block_unpadded_size(const lzma_block *)\00", align 1
@.str.2 = private unnamed_addr constant [38 x i8] c"vli <= ((18446744073709551615UL) / 2)\00", align 1
@.str.3 = private unnamed_addr constant [77 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/index.h\00", align 1
@__PRETTY_FUNCTION__.vli_ceil4 = private unnamed_addr constant [29 x i8] c"lzma_vli vli_ceil4(lzma_vli)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_block_compressed_size(%struct.lzma_block* %block, i64 %unpadded_size) #0 !dbg !32 {
entry:
  %retval = alloca i32, align 4
  %block.addr = alloca %struct.lzma_block*, align 8
  %unpadded_size.addr = alloca i64, align 8
  %container_size = alloca i32, align 4
  %compressed_size = alloca i64, align 8
  store %struct.lzma_block* %block, %struct.lzma_block** %block.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_block** %block.addr, metadata !106, metadata !107), !dbg !108
  store i64 %unpadded_size, i64* %unpadded_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %unpadded_size.addr, metadata !109, metadata !107), !dbg !110
  call void @llvm.dbg.declare(metadata i32* %container_size, metadata !111, metadata !107), !dbg !112
  call void @llvm.dbg.declare(metadata i64* %compressed_size, metadata !113, metadata !107), !dbg !114
  %0 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !115
  %call = call i64 @lzma_block_unpadded_size(%struct.lzma_block* %0) #6, !dbg !117
  %cmp = icmp eq i64 %call, 0, !dbg !118
  br i1 %cmp, label %if.then, label %if.end, !dbg !119

if.then:                                          ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !120
  br label %return, !dbg !120

if.end:                                           ; preds = %entry
  %1 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !121
  %header_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %1, i32 0, i32 1, !dbg !122
  %2 = load i32, i32* %header_size, align 4, !dbg !122
  %3 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !123
  %check = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %3, i32 0, i32 2, !dbg !124
  %4 = load i32, i32* %check, align 8, !dbg !124
  %call1 = call i32 @lzma_check_size(i32 %4) #1, !dbg !125
  %add = add i32 %2, %call1, !dbg !126
  store i32 %add, i32* %container_size, align 4, !dbg !127
  %5 = load i64, i64* %unpadded_size.addr, align 8, !dbg !128
  %6 = load i32, i32* %container_size, align 4, !dbg !130
  %conv = zext i32 %6 to i64, !dbg !130
  %cmp2 = icmp ule i64 %5, %conv, !dbg !131
  br i1 %cmp2, label %if.then4, label %if.end5, !dbg !132

if.then4:                                         ; preds = %if.end
  store i32 9, i32* %retval, align 4, !dbg !133
  br label %return, !dbg !133

if.end5:                                          ; preds = %if.end
  %7 = load i64, i64* %unpadded_size.addr, align 8, !dbg !134
  %8 = load i32, i32* %container_size, align 4, !dbg !135
  %conv6 = zext i32 %8 to i64, !dbg !135
  %sub = sub i64 %7, %conv6, !dbg !136
  store i64 %sub, i64* %compressed_size, align 8, !dbg !137
  %9 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !138
  %compressed_size7 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %9, i32 0, i32 3, !dbg !140
  %10 = load i64, i64* %compressed_size7, align 8, !dbg !140
  %cmp8 = icmp ne i64 %10, -1, !dbg !141
  br i1 %cmp8, label %land.lhs.true, label %if.end14, !dbg !142

land.lhs.true:                                    ; preds = %if.end5
  %11 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !143
  %compressed_size10 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %11, i32 0, i32 3, !dbg !145
  %12 = load i64, i64* %compressed_size10, align 8, !dbg !145
  %13 = load i64, i64* %compressed_size, align 8, !dbg !146
  %cmp11 = icmp ne i64 %12, %13, !dbg !147
  br i1 %cmp11, label %if.then13, label %if.end14, !dbg !148

if.then13:                                        ; preds = %land.lhs.true
  store i32 9, i32* %retval, align 4, !dbg !150
  br label %return, !dbg !150

if.end14:                                         ; preds = %land.lhs.true, %if.end5
  %14 = load i64, i64* %compressed_size, align 8, !dbg !151
  %15 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !152
  %compressed_size15 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %15, i32 0, i32 3, !dbg !153
  store i64 %14, i64* %compressed_size15, align 8, !dbg !154
  store i32 0, i32* %retval, align 4, !dbg !155
  br label %return, !dbg !155

return:                                           ; preds = %if.end14, %if.then13, %if.then4, %if.then
  %16 = load i32, i32* %retval, align 4, !dbg !156
  ret i32 %16, !dbg !156
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind readonly uwtable
define i64 @lzma_block_unpadded_size(%struct.lzma_block* %block) #2 !dbg !93 {
entry:
  %retval = alloca i64, align 8
  %block.addr = alloca %struct.lzma_block*, align 8
  %unpadded_size = alloca i64, align 8
  store %struct.lzma_block* %block, %struct.lzma_block** %block.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_block** %block.addr, metadata !157, metadata !107), !dbg !158
  call void @llvm.dbg.declare(metadata i64* %unpadded_size, metadata !159, metadata !107), !dbg !160
  %0 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !161
  %cmp = icmp eq %struct.lzma_block* %0, null, !dbg !163
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !164

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !165
  %version = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %1, i32 0, i32 0, !dbg !167
  %2 = load i32, i32* %version, align 8, !dbg !167
  %cmp1 = icmp ne i32 %2, 0, !dbg !168
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !169

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %3 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !170
  %header_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %3, i32 0, i32 1, !dbg !171
  %4 = load i32, i32* %header_size, align 4, !dbg !171
  %cmp3 = icmp ult i32 %4, 8, !dbg !172
  br i1 %cmp3, label %if.then, label %lor.lhs.false4, !dbg !173

lor.lhs.false4:                                   ; preds = %lor.lhs.false2
  %5 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !174
  %header_size5 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %5, i32 0, i32 1, !dbg !175
  %6 = load i32, i32* %header_size5, align 4, !dbg !175
  %cmp6 = icmp ugt i32 %6, 1024, !dbg !176
  br i1 %cmp6, label %if.then, label %lor.lhs.false7, !dbg !177

lor.lhs.false7:                                   ; preds = %lor.lhs.false4
  %7 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !178
  %header_size8 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %7, i32 0, i32 1, !dbg !179
  %8 = load i32, i32* %header_size8, align 4, !dbg !179
  %and = and i32 %8, 3, !dbg !180
  %tobool = icmp ne i32 %and, 0, !dbg !180
  br i1 %tobool, label %if.then, label %lor.lhs.false9, !dbg !181

lor.lhs.false9:                                   ; preds = %lor.lhs.false7
  %9 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !182
  %compressed_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %9, i32 0, i32 3, !dbg !182
  %10 = load i64, i64* %compressed_size, align 8, !dbg !182
  %cmp10 = icmp ule i64 %10, 9223372036854775807, !dbg !182
  br i1 %cmp10, label %lor.lhs.false14, label %lor.lhs.false11, !dbg !182

lor.lhs.false11:                                  ; preds = %lor.lhs.false9
  %11 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !183
  %compressed_size12 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %11, i32 0, i32 3, !dbg !183
  %12 = load i64, i64* %compressed_size12, align 8, !dbg !183
  %cmp13 = icmp eq i64 %12, -1, !dbg !183
  br i1 %cmp13, label %lor.lhs.false14, label %if.then, !dbg !185

lor.lhs.false14:                                  ; preds = %lor.lhs.false11, %lor.lhs.false9
  %13 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !186
  %compressed_size15 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %13, i32 0, i32 3, !dbg !187
  %14 = load i64, i64* %compressed_size15, align 8, !dbg !187
  %cmp16 = icmp eq i64 %14, 0, !dbg !188
  br i1 %cmp16, label %if.then, label %lor.lhs.false17, !dbg !189

lor.lhs.false17:                                  ; preds = %lor.lhs.false14
  %15 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !190
  %check = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %15, i32 0, i32 2, !dbg !191
  %16 = load i32, i32* %check, align 8, !dbg !191
  %cmp18 = icmp ugt i32 %16, 15, !dbg !192
  br i1 %cmp18, label %if.then, label %if.end, !dbg !193

if.then:                                          ; preds = %lor.lhs.false17, %lor.lhs.false14, %lor.lhs.false11, %lor.lhs.false7, %lor.lhs.false4, %lor.lhs.false2, %lor.lhs.false, %entry
  store i64 0, i64* %retval, align 8, !dbg !195
  br label %return, !dbg !195

if.end:                                           ; preds = %lor.lhs.false17
  %17 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !196
  %compressed_size19 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %17, i32 0, i32 3, !dbg !198
  %18 = load i64, i64* %compressed_size19, align 8, !dbg !198
  %cmp20 = icmp eq i64 %18, -1, !dbg !199
  br i1 %cmp20, label %if.then21, label %if.end22, !dbg !200

if.then21:                                        ; preds = %if.end
  store i64 -1, i64* %retval, align 8, !dbg !201
  br label %return, !dbg !201

if.end22:                                         ; preds = %if.end
  %19 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !202
  %compressed_size23 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %19, i32 0, i32 3, !dbg !203
  %20 = load i64, i64* %compressed_size23, align 8, !dbg !203
  %21 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !204
  %header_size24 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %21, i32 0, i32 1, !dbg !205
  %22 = load i32, i32* %header_size24, align 4, !dbg !205
  %conv = zext i32 %22 to i64, !dbg !204
  %add = add i64 %20, %conv, !dbg !206
  %23 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !207
  %check25 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %23, i32 0, i32 2, !dbg !208
  %24 = load i32, i32* %check25, align 8, !dbg !208
  %call = call i32 @lzma_check_size(i32 %24) #1, !dbg !209
  %conv26 = zext i32 %call to i64, !dbg !209
  %add27 = add i64 %add, %conv26, !dbg !210
  store i64 %add27, i64* %unpadded_size, align 8, !dbg !211
  %25 = load i64, i64* %unpadded_size, align 8, !dbg !212
  %cmp28 = icmp uge i64 %25, 5, !dbg !212
  br i1 %cmp28, label %cond.true, label %cond.false, !dbg !212

cond.true:                                        ; preds = %if.end22
  br label %cond.end, !dbg !213

cond.false:                                       ; preds = %if.end22
  call void @__assert_fail(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([82 x i8], [82 x i8]* @.str.1, i32 0, i32 0), i32 78, i8* getelementptr inbounds ([54 x i8], [54 x i8]* @__PRETTY_FUNCTION__.lzma_block_unpadded_size, i32 0, i32 0)) #7, !dbg !215
  unreachable, !dbg !215
                                                  ; No predecessors!
  br label %cond.end, !dbg !216

cond.end:                                         ; preds = %26, %cond.true
  %27 = load i64, i64* %unpadded_size, align 8, !dbg !218
  %cmp30 = icmp ugt i64 %27, 9223372036854775804, !dbg !220
  br i1 %cmp30, label %if.then32, label %if.end33, !dbg !221

if.then32:                                        ; preds = %cond.end
  store i64 0, i64* %retval, align 8, !dbg !222
  br label %return, !dbg !222

if.end33:                                         ; preds = %cond.end
  %28 = load i64, i64* %unpadded_size, align 8, !dbg !223
  store i64 %28, i64* %retval, align 8, !dbg !224
  br label %return, !dbg !224

return:                                           ; preds = %if.end33, %if.then32, %if.then21, %if.then
  %29 = load i64, i64* %retval, align 8, !dbg !225
  ret i64 %29, !dbg !225
}

; Function Attrs: nounwind readnone
declare i32 @lzma_check_size(i32) #3

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #4

; Function Attrs: nounwind readonly uwtable
define i64 @lzma_block_total_size(%struct.lzma_block* %block) #2 !dbg !98 {
entry:
  %block.addr = alloca %struct.lzma_block*, align 8
  %unpadded_size = alloca i64, align 8
  store %struct.lzma_block* %block, %struct.lzma_block** %block.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_block** %block.addr, metadata !226, metadata !107), !dbg !227
  call void @llvm.dbg.declare(metadata i64* %unpadded_size, metadata !228, metadata !107), !dbg !229
  %0 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !230
  %call = call i64 @lzma_block_unpadded_size(%struct.lzma_block* %0) #6, !dbg !231
  store i64 %call, i64* %unpadded_size, align 8, !dbg !229
  %1 = load i64, i64* %unpadded_size, align 8, !dbg !232
  %cmp = icmp ne i64 %1, -1, !dbg !234
  br i1 %cmp, label %if.then, label %if.end, !dbg !235

if.then:                                          ; preds = %entry
  %2 = load i64, i64* %unpadded_size, align 8, !dbg !236
  %call1 = call i64 @vli_ceil4(i64 %2), !dbg !237
  store i64 %call1, i64* %unpadded_size, align 8, !dbg !238
  br label %if.end, !dbg !239

if.end:                                           ; preds = %if.then, %entry
  %3 = load i64, i64* %unpadded_size, align 8, !dbg !240
  ret i64 %3, !dbg !241
}

; Function Attrs: inlinehint nounwind uwtable
define internal i64 @vli_ceil4(i64 %vli) #5 !dbg !99 {
entry:
  %vli.addr = alloca i64, align 8
  store i64 %vli, i64* %vli.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %vli.addr, metadata !242, metadata !107), !dbg !243
  %0 = load i64, i64* %vli.addr, align 8, !dbg !244
  %cmp = icmp ule i64 %0, 9223372036854775807, !dbg !244
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !244

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !245

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.3, i32 0, i32 0), i32 41, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @__PRETTY_FUNCTION__.vli_ceil4, i32 0, i32 0)) #7, !dbg !247
  unreachable, !dbg !247
                                                  ; No predecessors!
  br label %cond.end, !dbg !249

cond.end:                                         ; preds = %1, %cond.true
  %2 = load i64, i64* %vli.addr, align 8, !dbg !251
  %add = add i64 %2, 3, !dbg !252
  %and = and i64 %add, -4, !dbg !253
  ret i64 %and, !dbg !254
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readonly uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly }
attributes #7 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!103, !104}
!llvm.ident = !{!105}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !28, subprograms: !31)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/block_util.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
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
!28 = !{!29, !30}
!29 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!30 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!31 = !{!32, !93, !98, !99}
!32 = distinct !DISubprogram(name: "lzma_block_compressed_size", scope: !1, file: !1, line: 18, type: !33, isLocal: false, isDefinition: true, scopeLine: 19, flags: DIFlagPrototyped, isOptimized: false, variables: !92)
!33 = !DISubroutineType(types: !34)
!34 = !{!35, !36, !48}
!35 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64, align: 64)
!37 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_block", file: !38, line: 245, baseType: !39)
!38 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/block.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!39 = !DICompositeType(tag: DW_TAG_structure_type, file: !38, line: 30, size: 1664, align: 64, elements: !40)
!40 = !{!41, !44, !45, !47, !52, !53, !61, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !80, !81, !82, !83, !85, !86, !87, !88, !89, !90, !91}
!41 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !39, file: !38, line: 47, baseType: !42, size: 32, align: 32)
!42 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !43, line: 51, baseType: !30)
!43 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!44 = !DIDerivedType(tag: DW_TAG_member, name: "header_size", scope: !39, file: !38, line: 67, baseType: !42, size: 32, align: 32, offset: 32)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !39, file: !38, line: 88, baseType: !46, size: 32, align: 32, offset: 64)
!46 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !19, line: 55, baseType: !18)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_size", scope: !39, file: !38, line: 143, baseType: !48, size: 64, align: 64, offset: 128)
!48 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !49, line: 63, baseType: !50)
!49 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!50 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !43, line: 55, baseType: !51)
!51 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !39, file: !38, line: 167, baseType: !48, size: 64, align: 64, offset: 192)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "filters", scope: !39, file: !38, line: 195, baseType: !54, size: 64, align: 64, offset: 256)
!54 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!55 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !56, line: 65, baseType: !57)
!56 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!57 = !DICompositeType(tag: DW_TAG_structure_type, file: !56, line: 43, size: 128, align: 64, elements: !58)
!58 = !{!59, !60}
!59 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !57, file: !56, line: 54, baseType: !48, size: 64, align: 64)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !57, file: !56, line: 63, baseType: !29, size: 64, align: 64, offset: 64)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "raw_check", scope: !39, file: !38, line: 212, baseType: !62, size: 512, align: 8, offset: 320)
!62 = !DICompositeType(tag: DW_TAG_array_type, baseType: !63, size: 512, align: 8, elements: !65)
!63 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !43, line: 48, baseType: !64)
!64 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!65 = !{!66}
!66 = !DISubrange(count: 64)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !39, file: !38, line: 221, baseType: !29, size: 64, align: 64, offset: 832)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !39, file: !38, line: 222, baseType: !29, size: 64, align: 64, offset: 896)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !39, file: !38, line: 223, baseType: !29, size: 64, align: 64, offset: 960)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !39, file: !38, line: 224, baseType: !42, size: 32, align: 32, offset: 1024)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !39, file: !38, line: 225, baseType: !42, size: 32, align: 32, offset: 1056)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !39, file: !38, line: 226, baseType: !48, size: 64, align: 64, offset: 1088)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !39, file: !38, line: 227, baseType: !48, size: 64, align: 64, offset: 1152)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !39, file: !38, line: 228, baseType: !48, size: 64, align: 64, offset: 1216)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !39, file: !38, line: 229, baseType: !48, size: 64, align: 64, offset: 1280)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !39, file: !38, line: 230, baseType: !48, size: 64, align: 64, offset: 1344)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !39, file: !38, line: 231, baseType: !48, size: 64, align: 64, offset: 1408)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !39, file: !38, line: 232, baseType: !79, size: 32, align: 32, offset: 1472)
!79 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !25)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !39, file: !38, line: 233, baseType: !79, size: 32, align: 32, offset: 1504)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !39, file: !38, line: 234, baseType: !79, size: 32, align: 32, offset: 1536)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !39, file: !38, line: 235, baseType: !79, size: 32, align: 32, offset: 1568)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool1", scope: !39, file: !38, line: 236, baseType: !84, size: 8, align: 8, offset: 1600)
!84 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !4, line: 29, baseType: !64)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool2", scope: !39, file: !38, line: 237, baseType: !84, size: 8, align: 8, offset: 1608)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool3", scope: !39, file: !38, line: 238, baseType: !84, size: 8, align: 8, offset: 1616)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool4", scope: !39, file: !38, line: 239, baseType: !84, size: 8, align: 8, offset: 1624)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool5", scope: !39, file: !38, line: 240, baseType: !84, size: 8, align: 8, offset: 1632)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool6", scope: !39, file: !38, line: 241, baseType: !84, size: 8, align: 8, offset: 1640)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool7", scope: !39, file: !38, line: 242, baseType: !84, size: 8, align: 8, offset: 1648)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool8", scope: !39, file: !38, line: 243, baseType: !84, size: 8, align: 8, offset: 1656)
!92 = !{}
!93 = distinct !DISubprogram(name: "lzma_block_unpadded_size", scope: !1, file: !1, line: 49, type: !94, isLocal: false, isDefinition: true, scopeLine: 50, flags: DIFlagPrototyped, isOptimized: false, variables: !92)
!94 = !DISubroutineType(types: !95)
!95 = !{!48, !96}
!96 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !97, size: 64, align: 64)
!97 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !37)
!98 = distinct !DISubprogram(name: "lzma_block_total_size", scope: !1, file: !1, line: 87, type: !94, isLocal: false, isDefinition: true, scopeLine: 88, flags: DIFlagPrototyped, isOptimized: false, variables: !92)
!99 = distinct !DISubprogram(name: "vli_ceil4", scope: !100, file: !100, line: 39, type: !101, isLocal: true, isDefinition: true, scopeLine: 40, flags: DIFlagPrototyped, isOptimized: false, variables: !92)
!100 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/index.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!101 = !DISubroutineType(types: !102)
!102 = !{!48, !48}
!103 = !{i32 2, !"Dwarf Version", i32 4}
!104 = !{i32 2, !"Debug Info Version", i32 3}
!105 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!106 = !DILocalVariable(name: "block", arg: 1, scope: !32, file: !1, line: 18, type: !36)
!107 = !DIExpression()
!108 = !DILocation(line: 18, column: 40, scope: !32)
!109 = !DILocalVariable(name: "unpadded_size", arg: 2, scope: !32, file: !1, line: 18, type: !48)
!110 = !DILocation(line: 18, column: 56, scope: !32)
!111 = !DILocalVariable(name: "container_size", scope: !32, file: !1, line: 20, type: !42)
!112 = !DILocation(line: 20, column: 11, scope: !32)
!113 = !DILocalVariable(name: "compressed_size", scope: !32, file: !1, line: 21, type: !48)
!114 = !DILocation(line: 21, column: 11, scope: !32)
!115 = !DILocation(line: 24, column: 31, scope: !116)
!116 = distinct !DILexicalBlock(scope: !32, file: !1, line: 24, column: 6)
!117 = !DILocation(line: 24, column: 6, scope: !116)
!118 = !DILocation(line: 24, column: 38, scope: !116)
!119 = !DILocation(line: 24, column: 6, scope: !32)
!120 = !DILocation(line: 25, column: 3, scope: !116)
!121 = !DILocation(line: 27, column: 19, scope: !32)
!122 = !DILocation(line: 27, column: 26, scope: !32)
!123 = !DILocation(line: 28, column: 22, scope: !32)
!124 = !DILocation(line: 28, column: 29, scope: !32)
!125 = !DILocation(line: 28, column: 6, scope: !32)
!126 = !DILocation(line: 28, column: 4, scope: !32)
!127 = !DILocation(line: 27, column: 17, scope: !32)
!128 = !DILocation(line: 31, column: 6, scope: !129)
!129 = distinct !DILexicalBlock(scope: !32, file: !1, line: 31, column: 6)
!130 = !DILocation(line: 31, column: 23, scope: !129)
!131 = !DILocation(line: 31, column: 20, scope: !129)
!132 = !DILocation(line: 31, column: 6, scope: !32)
!133 = !DILocation(line: 32, column: 3, scope: !129)
!134 = !DILocation(line: 37, column: 20, scope: !32)
!135 = !DILocation(line: 37, column: 36, scope: !32)
!136 = !DILocation(line: 37, column: 34, scope: !32)
!137 = !DILocation(line: 37, column: 18, scope: !32)
!138 = !DILocation(line: 38, column: 6, scope: !139)
!139 = distinct !DILexicalBlock(scope: !32, file: !1, line: 38, column: 6)
!140 = !DILocation(line: 38, column: 13, scope: !139)
!141 = !DILocation(line: 38, column: 29, scope: !139)
!142 = !DILocation(line: 39, column: 4, scope: !139)
!143 = !DILocation(line: 39, column: 7, scope: !144)
!144 = !DILexicalBlockFile(scope: !139, file: !1, discriminator: 1)
!145 = !DILocation(line: 39, column: 14, scope: !144)
!146 = !DILocation(line: 39, column: 33, scope: !144)
!147 = !DILocation(line: 39, column: 30, scope: !144)
!148 = !DILocation(line: 38, column: 6, scope: !149)
!149 = !DILexicalBlockFile(scope: !32, file: !1, discriminator: 1)
!150 = !DILocation(line: 40, column: 3, scope: !139)
!151 = !DILocation(line: 42, column: 27, scope: !32)
!152 = !DILocation(line: 42, column: 2, scope: !32)
!153 = !DILocation(line: 42, column: 9, scope: !32)
!154 = !DILocation(line: 42, column: 25, scope: !32)
!155 = !DILocation(line: 44, column: 2, scope: !32)
!156 = !DILocation(line: 45, column: 1, scope: !32)
!157 = !DILocalVariable(name: "block", arg: 1, scope: !93, file: !1, line: 49, type: !96)
!158 = !DILocation(line: 49, column: 44, scope: !93)
!159 = !DILocalVariable(name: "unpadded_size", scope: !93, file: !1, line: 51, type: !48)
!160 = !DILocation(line: 51, column: 11, scope: !93)
!161 = !DILocation(line: 59, column: 6, scope: !162)
!162 = distinct !DILexicalBlock(scope: !93, file: !1, line: 59, column: 6)
!163 = !DILocation(line: 59, column: 12, scope: !162)
!164 = !DILocation(line: 59, column: 20, scope: !162)
!165 = !DILocation(line: 59, column: 23, scope: !166)
!166 = !DILexicalBlockFile(scope: !162, file: !1, discriminator: 1)
!167 = !DILocation(line: 59, column: 30, scope: !166)
!168 = !DILocation(line: 59, column: 38, scope: !166)
!169 = !DILocation(line: 60, column: 4, scope: !162)
!170 = !DILocation(line: 60, column: 7, scope: !166)
!171 = !DILocation(line: 60, column: 14, scope: !166)
!172 = !DILocation(line: 60, column: 26, scope: !166)
!173 = !DILocation(line: 61, column: 4, scope: !162)
!174 = !DILocation(line: 61, column: 7, scope: !166)
!175 = !DILocation(line: 61, column: 14, scope: !166)
!176 = !DILocation(line: 61, column: 26, scope: !166)
!177 = !DILocation(line: 62, column: 4, scope: !162)
!178 = !DILocation(line: 62, column: 8, scope: !166)
!179 = !DILocation(line: 62, column: 15, scope: !166)
!180 = !DILocation(line: 62, column: 27, scope: !166)
!181 = !DILocation(line: 63, column: 4, scope: !162)
!182 = !DILocation(line: 63, column: 8, scope: !166)
!183 = !DILocation(line: 63, column: 8, scope: !184)
!184 = !DILexicalBlockFile(scope: !162, file: !1, discriminator: 2)
!185 = !DILocation(line: 64, column: 4, scope: !162)
!186 = !DILocation(line: 64, column: 7, scope: !166)
!187 = !DILocation(line: 64, column: 14, scope: !166)
!188 = !DILocation(line: 64, column: 30, scope: !166)
!189 = !DILocation(line: 65, column: 4, scope: !162)
!190 = !DILocation(line: 65, column: 22, scope: !166)
!191 = !DILocation(line: 65, column: 29, scope: !166)
!192 = !DILocation(line: 65, column: 36, scope: !166)
!193 = !DILocation(line: 59, column: 6, scope: !194)
!194 = !DILexicalBlockFile(scope: !93, file: !1, discriminator: 2)
!195 = !DILocation(line: 66, column: 3, scope: !162)
!196 = !DILocation(line: 70, column: 6, scope: !197)
!197 = distinct !DILexicalBlock(scope: !93, file: !1, line: 70, column: 6)
!198 = !DILocation(line: 70, column: 13, scope: !197)
!199 = !DILocation(line: 70, column: 29, scope: !197)
!200 = !DILocation(line: 70, column: 6, scope: !93)
!201 = !DILocation(line: 71, column: 3, scope: !197)
!202 = !DILocation(line: 74, column: 18, scope: !93)
!203 = !DILocation(line: 74, column: 25, scope: !93)
!204 = !DILocation(line: 75, column: 7, scope: !93)
!205 = !DILocation(line: 75, column: 14, scope: !93)
!206 = !DILocation(line: 75, column: 5, scope: !93)
!207 = !DILocation(line: 76, column: 23, scope: !93)
!208 = !DILocation(line: 76, column: 30, scope: !93)
!209 = !DILocation(line: 76, column: 7, scope: !93)
!210 = !DILocation(line: 76, column: 5, scope: !93)
!211 = !DILocation(line: 74, column: 16, scope: !93)
!212 = !DILocation(line: 78, column: 2, scope: !93)
!213 = !DILocation(line: 78, column: 2, scope: !214)
!214 = !DILexicalBlockFile(scope: !93, file: !1, discriminator: 1)
!215 = !DILocation(line: 78, column: 2, scope: !194)
!216 = !DILocation(line: 78, column: 2, scope: !217)
!217 = !DILexicalBlockFile(scope: !93, file: !1, discriminator: 3)
!218 = !DILocation(line: 79, column: 6, scope: !219)
!219 = distinct !DILexicalBlock(scope: !93, file: !1, line: 79, column: 6)
!220 = !DILocation(line: 79, column: 20, scope: !219)
!221 = !DILocation(line: 79, column: 6, scope: !93)
!222 = !DILocation(line: 80, column: 3, scope: !219)
!223 = !DILocation(line: 82, column: 9, scope: !93)
!224 = !DILocation(line: 82, column: 2, scope: !93)
!225 = !DILocation(line: 83, column: 1, scope: !93)
!226 = !DILocalVariable(name: "block", arg: 1, scope: !98, file: !1, line: 87, type: !96)
!227 = !DILocation(line: 87, column: 41, scope: !98)
!228 = !DILocalVariable(name: "unpadded_size", scope: !98, file: !1, line: 89, type: !48)
!229 = !DILocation(line: 89, column: 11, scope: !98)
!230 = !DILocation(line: 89, column: 52, scope: !98)
!231 = !DILocation(line: 89, column: 27, scope: !98)
!232 = !DILocation(line: 91, column: 6, scope: !233)
!233 = distinct !DILexicalBlock(scope: !98, file: !1, line: 91, column: 6)
!234 = !DILocation(line: 91, column: 20, scope: !233)
!235 = !DILocation(line: 91, column: 6, scope: !98)
!236 = !DILocation(line: 92, column: 29, scope: !233)
!237 = !DILocation(line: 92, column: 19, scope: !233)
!238 = !DILocation(line: 92, column: 17, scope: !233)
!239 = !DILocation(line: 92, column: 3, scope: !233)
!240 = !DILocation(line: 94, column: 9, scope: !98)
!241 = !DILocation(line: 94, column: 2, scope: !98)
!242 = !DILocalVariable(name: "vli", arg: 1, scope: !99, file: !100, line: 39, type: !48)
!243 = !DILocation(line: 39, column: 20, scope: !99)
!244 = !DILocation(line: 41, column: 2, scope: !99)
!245 = !DILocation(line: 41, column: 2, scope: !246)
!246 = !DILexicalBlockFile(scope: !99, file: !100, discriminator: 1)
!247 = !DILocation(line: 41, column: 2, scope: !248)
!248 = !DILexicalBlockFile(scope: !99, file: !100, discriminator: 2)
!249 = !DILocation(line: 41, column: 2, scope: !250)
!250 = !DILexicalBlockFile(scope: !99, file: !100, discriminator: 3)
!251 = !DILocation(line: 42, column: 10, scope: !99)
!252 = !DILocation(line: 42, column: 14, scope: !99)
!253 = !DILocation(line: 42, column: 19, scope: !99)
!254 = !DILocation(line: 42, column: 2, scope: !99)
